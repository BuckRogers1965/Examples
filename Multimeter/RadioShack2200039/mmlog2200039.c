#ifndef	lint
static char *Sccsid __attribute__ ((unused)) = "%Z%%M% %I% %G% John Rehwinkel KG4L";
#endif

/* log data from Radio Shack 2200039 Digital Multimeter w/ USB 

  James M. Rogers
  15 Nov 2014
  Refreshing some older code for a newer
  radio shack usb 46 range digital multimeter.


  I got the code from this link:
    http://www.vitriol.com/ftp/mmlog.c

  and merged the code with this even older code: 
    http://www.mungewell.org/ut61b/ut60e_simple.c

  So that the tty code would restart after I stopped the code.
*/


#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#define CKSUMOFF	0x57	/* checksum offset */
#define SEGBITS		0xf7	/* digit segment bits */
#define DPBIT		0x08	/* decimal point bit */
#define NODIGIT		-1	/* no digit */
#define NMODES		26	/* number of mode values */
#define NBYTES		0x100	/* number of possible bytes */

#define TRUE		1	/* boolean `true' */
#define FALSE		0	/* boolean `false' */

#define ARGCHAR		'-'	/* argument delimiter */
#define PATHSEP		'/'	/* path separator */

#define GETINT(s, x)	(sscanf(s, Int, x) == 1)
#define Baud		B4800

struct frame
{
  unsigned char mode;	 /* multimeter mode */
  unsigned char units1;	 /* units and other flags */
  unsigned char units2;	 /* more units and stuff */
  unsigned char digit4;	 /* digit 4 */
  unsigned char digit3;	 /* digit 3 */
  unsigned char digit2;	 /* digit 2 */
  unsigned char digit1;	 /* digit 1 */
  unsigned char flags;	 /* flags */
  unsigned char cksum;	 /* checksum */
};

typedef struct frame frame_t;

struct digit
{
  unsigned segments;	 /* segment bits */
  int digit;		 /* resulting digit */
};

typedef struct digit digit_t;

static int openport (char *path);
static int checksum (frame_t * fp);
static void init (void);
static void monitor (int);
static void printframe (frame_t * fp);
static void printvalue (frame_t * fp);
static void myread (int fd, void *bp, size_t len);
static void setprog (char *name);
static void dprint (char *fmt, ...);
static void error (char *fmt, ...);
static void whyerror (char *fmt, ...);
static void *mkbuf (int size);

char *modes[] = {
  "DC V",
  "AC V",
  "DC uA",
  "DC mA",
  "DC A",
  "AC uA",
  "AC mA",
  "AC A",
  "OHM",
  "CAP",
  "HZ",
  "NET HZ",
  "AMP HZ",
  "DUTY",
  "NET DUTY",
  "AMP DUTY",
  "WIDTH",
  "NET WIDTH",
  "AMP WIDTH",
  "DIODE",
  "CONT",
  "HFE",
  "LOGIC",
  "DBM",
  "EF",
  "TEMP"
};

digit_t digits[] = {
  {0xd7, '0'},
  {0x50, '1'},
  {0xb5, '2'},
  {0xf1, '3'},
  {0x72, '4'},
  {0xe3, '5'},
  {0xe6, '6'},
  {0xe7, '6'},
  {0x51, '7'},
  {0xf7, '8'},
  {0x73, '9'},
  {0xf3, '9'},
  {0x20, '-'},
  {0, NODIGIT}
};

static char *Usage = "Usage: %s [-mv] [-t #] [-o <path>] [-d /dev/tty]";
static char *Dev = "/dev/ttyUSB0";
static char *Int = "%i";
static char *Write = "w";

static int debugflag;		/* debug flag */
static int showmode;		/* show mode */
static int valueonly;		/* only show value */
static int interval;		/* time interval */
static char *prog;		/* program name */
static unsigned char *ddecode;	/* digit decode array */
static FILE *ofp;		/* input file pointer */

int
main (int argc,			/* argument count */
      char **argv,		/* argument vector */
      char **envp)
{				/* environment pointer */
  char *va;			/* value array */
  char *nvp;			/* needed value pointer */
  char *cvp;			/* current value pointer */
  char *evp;			/* end of value pointers */

  setprog (*argv);

  va = (char *) mkbuf (argc);
  nvp = va;
  cvp = va;
  evp = va + argc;
  ofp = stdout;
  interval = 0;
  debugflag = FALSE;
  showmode = FALSE;
  valueonly = FALSE;

  while (--argc) {
    if (**++argv == ARGCHAR) {
      while (*++*argv) {
	switch (**argv) {
	case 'd':		/* device */
	case 'o':		/* output file */
	case 't':		/* time interval */
	  if (nvp == evp) {
	    error (Usage, prog);
	  }
	  *nvp++ = **argv;
	  break;

	case 'm':		/* show mode */
	  showmode = TRUE;
	  break;

	case 'v':		/* value only */
	  valueonly = TRUE;
	  break;

	case 'D':		/* debug */
	  debugflag = TRUE;
	  break;

	default:
	  error (Usage, prog);
	}
      }
    }
    else {
      if (nvp > cvp) {
	switch (*cvp++) {
	case 'd':		/* device */
	  Dev = *argv;
	  break;

	case 'o':		/* output file */
	  ofp = fopen (*argv, Write);

	  if (ofp == NULL) {
	    whyerror (*argv);
	  }
	  break;

	case 't':		/* time interval */
	  if (!GETINT (*argv, &interval)) {
	    error (Usage, prog);
	  }

	  break;
	}
      }
      else {
	error (Usage, prog);
      }
    }
  }

  if (nvp > cvp) {
    error (Usage, prog);
  }

  free (va);

  init ();

  monitor (openport (Dev));

  return 0;
}

/* initialize */

static void
init (void)
{
  unsigned char *dp;		/* decode pointer */
  unsigned char *de;		/* decode end */
  digit_t *dep;			/* digit encode pointer */

  ddecode = (unsigned char *) mkbuf (NBYTES);
  de = ddecode + NBYTES;

  for (dp = ddecode; dp < de; dp++) {
    *dp = '?';
  }

  for (dep = digits; dep->digit != NODIGIT; dep++) {
    ddecode[dep->segments] = dep->digit;
  }
}

/* monitor RS-232 traffic */

static void
monitor (int fd)
{
  time_t now;			/* current time */
  time_t last;			/* last print time */
  time_t start;			/* start time */
  frame_t buf;			/* incoming frame */

  last = 0;
  start = time (NULL);

  for (;;) {
    myread (fd, &buf, sizeof (buf));

    while (!checksum (&buf)) {
      bcopy ((char *) &buf + 1, (char *) &buf, sizeof (buf) - 1);

      myread (fd, (char *) &buf + sizeof (buf) - 1, 1);
    }

    if (interval != 0) {
      now = time (NULL);

      if ((now - last) >= interval) {
	fprintf (ofp, "%d\t", (int) (now - start));

	printframe (&buf);
	last = now;
      }
    }
    else {
      printframe (&buf);
    }
  }
}

/* print data frame */

static void
printframe (frame_t * fp)
{				/* frame pointer */
  if (valueonly) {
    printvalue (fp);
    return;
  }

  if (showmode && (fp->mode < NMODES)) {
    fprintf (ofp, "%s: ", modes[fp->mode]);
  }

  if (fp->flags & 0x04) {
    fprintf (ofp, "~ ");
  }

  if (fp->flags & 0x08) {
    fprintf (ofp, "-");
  }

  putc (ddecode[fp->digit1 & SEGBITS], ofp);

  if (fp->digit2 & DPBIT) {
    putc ('.', ofp);
  }

  putc (ddecode[fp->digit2 & SEGBITS], ofp);

  if (fp->digit3 & DPBIT) {
    putc ('.', ofp);
  }

  putc (ddecode[fp->digit3 & SEGBITS], ofp);

  if (fp->digit4 & DPBIT) {
    putc ('.', ofp);
  }

  if (fp->digit4 == 0x27) {
    fprintf (ofp, "F");
    goto finish;
  }

  if (fp->digit4 == 0x87) {
    fprintf (ofp, "C");
    goto finish;

  }

  putc (ddecode[fp->digit4 & SEGBITS], ofp);

  if (fp->units1 & 0x20) {
    fprintf (ofp, " K");
  }

  if (fp->units1 & 0x10) {
    fprintf (ofp, " M");
  }

  if (fp->units1 & 0x01) {
    fprintf (ofp, " m");
  }

  if (fp->units2 & 0x80) {
    fprintf (ofp, " u");
  }

  if (fp->units2 & 0x40) {
    fprintf (ofp, " n");
  }

  if (fp->units1 & 0x80) {
    fprintf (ofp, "Hz");
  }

  if (fp->units1 & 0x40) {
    fprintf (ofp, "Ohm");
  }

  if (fp->units1 & 0x08) {
    fprintf (ofp, "F");
  }

  if (fp->units1 & 0x04) {
    fprintf (ofp, "A");
  }

  if (fp->units1 & 0x02) {
    fprintf (ofp, "V");
  }

  if (fp->units2 & 0x20) {
    fprintf (ofp, "dBm");
  }

  if (fp->units2 & 0x10) {
    fprintf (ofp, "S");
  }

  if (fp->units2 & 0x08) {
    fprintf (ofp, "%%");
  }

  if (fp->units2 & 0x04) {
    fprintf (ofp, " hFE");
  }

  if (fp->units2 & 0x02) {
    fprintf (ofp, " REL");
  }

  if (fp->units2 & 0x01) {
    fprintf (ofp, " MIN");
  }

  if (fp->digit1 & 0x08) {
    fprintf (ofp, " MAX");
  }

  if (fp->flags & 0x80) {
    fprintf (ofp, " BEEP");
  }

  if (fp->flags & 0x40) {
    fprintf (ofp, " DIODE");
  }

  if (fp->flags & 0x10) {
    fprintf (ofp, " HOLD");
  }

  if (fp->flags & 0x02) {
    fprintf (ofp, " RS-232");
  }

  if (fp->flags & 0x01) {
    fprintf (ofp, " AUTO");
  }

finish:
  if (fp->flags & 0x20) {
    fprintf (ofp, " BAT");
  }


  fprintf (ofp, "\n");
}

/* print value */

static void
printvalue (frame_t * fp)
{				/* frame pointer */
  int digit;			/* digit */
  unsigned char *dp;		/* digit pointer */
  double value;			/* value accumulator */

  value = 0;
  dp = &fp->digit1;

  for (dp = &fp->digit1; dp >= &fp->digit4; dp--) {
    value *= 10;
    digit = ddecode[*dp & SEGBITS];

    if (digit == '?') {
      return;
    }

    if (digit == '-') {
      return;
    }

    value += digit - '0';
  }

  if (fp->digit2 & DPBIT) {
    value /= 1000;
  }

  if (fp->digit3 & DPBIT) {
    value /= 100;
  }

  if (fp->digit4 & DPBIT) {
    value /= 10;
  }

  if (fp->flags & 0x08) {
    value = -value;
  }

  if (fp->units1 & 0x20) {
    value *= 1e3;
  }

  if (fp->units1 & 0x10) {
    value *= 1e6;
  }

  if (fp->units1 & 0x01) {
    value /= 1e3;
  }

  if (fp->units2 & 0x80) {
    value /= 1e6;
  }

  if (fp->units2 & 0x40) {
    value /= 1e9;
  }

  fprintf (ofp, "%f\n", value);
}

/* verify frame checksum */

static int
checksum (frame_t * fp)
{				/* frame pointer */
  unsigned char sum;		/* running sum */

  dprint ("%02x %02x %02x %02x %02x %02x %02x %02x [%02x]",
	  fp->mode, fp->units1, fp->units2, fp->digit1, fp->digit2, fp->digit3, fp->digit4, fp->flags, fp->cksum);

  sum = (fp->mode + fp->units1 + fp->units2 + fp->digit1 + fp->digit2 + fp->digit3 + fp->digit4 + fp->flags + 0x39) & 0xff;

  dprint ("sum = %#02x, cksum = %#02x", sum, fp->cksum);

  return (sum == fp->cksum);
}

/* read from a port */

static void
myread (int fd,			/* file descriptor to read from */
	void *bp,		/* buffer pointer */
	size_t len)
{				/* amount to read */
  int nxfer;			/* number of bytes transferred */

  for (;;) {
    nxfer = read (fd, bp, len);

    if (nxfer < 0) {
      whyerror ("read(%d)", len);
    }

    if (nxfer == len) {
      return;
    }
  }
}

/* open and configure a serial port */

static int
openport (char *path)
{				/* path to serial port */
  int fd;			/* file descriptor */
  unsigned int mcr;
  struct termios newtio;
  bzero (&newtio, sizeof (newtio));

  fd = open (path, O_RDONLY | O_NOCTTY);

  if (fd < 0) {
    whyerror (path);
  }

  newtio.c_cflag = Baud | CS8 | CLOCAL | CREAD;
  newtio.c_iflag = ICRNL;
  newtio.c_oflag = 0;
  newtio.c_lflag = ~ICANON;

  newtio.c_cc[VINTR] = 0;	/* Ctrl-c */
  newtio.c_cc[VQUIT] = 0;	/* Ctrl-\ */
  newtio.c_cc[VERASE] = 0;	/* del */
  newtio.c_cc[VKILL] = 0;	/* @ */
  newtio.c_cc[VEOF] = 0;	/* Ctrl-d */
  newtio.c_cc[VTIME] = 1;	/* inter-character timer unused */
  newtio.c_cc[VMIN] = 14;	/* blocking read until 1 character arrives */
  newtio.c_cc[VSWTC] = 0;	/* '\0' */
  newtio.c_cc[VSTART] = 17;	/* Ctrl-q */
  newtio.c_cc[VSTOP] = 19;	/* Ctrl-s */
  newtio.c_cc[VSUSP] = 0;	/* Ctrl-z */
  newtio.c_cc[VEOL] = 0;	/* '\0' */
  newtio.c_cc[VREPRINT] = 0;	/* Ctrl-r */
  newtio.c_cc[VDISCARD] = 0;	/* Ctrl-u */
  newtio.c_cc[VWERASE] = 0;	/* Ctrl-w */
  newtio.c_cc[VLNEXT] = 0;	/* Ctrl-v */
  newtio.c_cc[VEOL2] = 0;	/* '\0' */

  tcsetattr (fd, TCSANOW, &newtio);
  mcr = 0;
  ioctl (fd, TIOCMGET, &mcr);
  mcr &= ~TIOCM_RTS;
  mcr |= TIOCM_DTR;
  ioctl (fd, TIOCMSET, &mcr);
  tcflush (fd, TCIFLUSH);

  return fd;
}

/* set currently running program name */

static void
setprog (char *name)
{				/* program name to use */
  prog = strrchr (name, PATHSEP);

  if (prog) {
    prog++;
  }
  else {
    prog = name;
  }
}

/* print out debug message (if enabled) */

static void
dprint (char *fmt,		/* message format */
	...)
{				/* format arguments */
  va_list ap;			/* argument pointer */

  if (debugflag == FALSE) {
    return;
  }

  fflush (stdout);

  va_start (ap, fmt);

  vfprintf (stderr, fmt, ap);

  va_end (ap);

  fprintf (stderr, "\n");
}

/* print out message and exit */

static void
error (char *fmt,		/* message format */
       ...)
{				/* format arguments */
  va_list ap;			/* argument pointer */

  fflush (stdout);

  fprintf (stderr, "%s: ", prog);

  va_start (ap, fmt);

  vfprintf (stderr, fmt, ap);

  va_end (ap);

  fprintf (stderr, "\n");

  exit (EINVAL);
}

/* print out error message and reason and exit */

static void
whyerror (char *fmt,		/* message format */
	  ...)
{				/* format arguments */
  char *errstr;			/* error string pointer */
  va_list ap;			/* argument pointer */

  fflush (stdout);

  fprintf (stderr, "%s: ", prog);

  va_start (ap, fmt);

  vfprintf (stderr, fmt, ap);

  va_end (ap);

  errstr = strerror (errno);

  if (errstr) {
    fprintf (stderr, ": %s\n", errstr);
  }
  else {
    fprintf (stderr, ": errno=%d\n", errno);
  }

  if (errno) {
    exit (errno);
  }
  else {
    exit (EINVAL);
  }
}

/* allocate a buffer and punt on failure */

static void *
mkbuf (int size)
{				/* size of buffer to allocate */
  void *ptr;			/* address of new buffer */

  ptr = malloc (size);

  if (ptr == NULL) {
    whyerror ("Malloc(%d)", size);
  }

  return ptr;
}
