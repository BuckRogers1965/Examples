LIBS=
CC=gcc
CFLAGS=
CPPFLAGS=
LDFLAGS=
AWK=

INSTALLCMD=@INSTALL@

VPATH=@srcdir@
srcdir=@srcdir@
builddir=@builddir@
SHELL=/bin/sh

BASEDIR= @prefix@
BINDIR = @bindir@
# we don't use sbindir because we want full compatibility with
# the previous releases of Samba
SBINDIR = @bindir@
LIBDIR = @libdir@
VARDIR = @localstatedir@
MANDIR = @mandir@

# The permissions to give the executables
INSTALLPERMS = 0755

PROGS = hl7 

######################################################################
# object file lists
######################################################################

OBJ = main.o ipc.o

######################################################################
# now the rules...
######################################################################

all : CHECK $(PROGS) 

.SUFFIXES: .c .o .po .po32

CHECK:
	@echo "Using FLAGS = $(FLAGS)"
	@echo "Using LIBS = $(LIBS)"

MAKEDIR = || exec false; \
	  if test -d "$$dir"; then :; else \
	  echo mkdir "$$dir"; \
	  mkdir -p "$$dir" >/dev/null 2>&1 || \
	  test -d "$$dir" || \
	  mkdir "$$dir" || \
	  exec false; fi || exec false

hl7: $(OBJ) main.o ipc.o
	@echo Linking $@
	@$(CC) $(FLAGS) -o $@ $(OBJ) $(LDFLAGS) $(LIBS) 

install: installbin installman installscripts installcp installswat

installdirs:
	$(SHELL) $(srcdir)/install-sh -d -m $(INSTALLPERMS) \
	$(BASEDIR) $(SBINDIR) $(BINDIR) $(LIBDIR) $(VARDIR) $(CODEPAGEDIR)

installbin: all installdirs
	@$(SHELL) $(srcdir)/script/installbin.sh $(INSTALLPERMS) $(BASEDIR) $(SBINDIR) $(LIBDIR) $(VARDIR) $(SPROGS)
	@$(SHELL) $(srcdir)/script/installbin.sh $(INSTALLPERMS) $(BASEDIR) $(BINDIR) $(LIBDIR) $(VARDIR) $(PROGS)

installscripts: installdirs
	@$(SHELL) $(srcdir)/script/installscripts.sh $(INSTALLPERMS) $(BINDIR) $(SCRIPTS)

installcp: installdirs
	@$(SHELL) $(srcdir)/script/installcp.sh $(srcdir) $(LIBDIR) $(CODEPAGEDIR) $(BINDIR) $(CODEPAGELIST)

installswat: installdirs
	@$(SHELL) $(srcdir)/script/installswat.sh $(SWATDIR) $(srcdir)

# revert to the previously installed version
revert:
	@$(SHELL) $(srcdir)/script/revert.sh $(SBINDIR) $(SPROGS) 
	@$(SHELL) $(srcdir)/script/revert.sh $(BINDIR) $(PROGS) $(SCRIPTS)

installman:
	@$(SHELL) $(srcdir)/script/installman.sh $(MANDIR) $(srcdir) "@ROFF@"

uninstall: uninstallman uninstallbin uninstallscripts uninstallcp

uninstallman:
	@$(SHELL) $(srcdir)/script/uninstallman.sh $(MANDIR) $(srcdir)

uninstallbin:
	@$(SHELL) $(srcdir)/script/uninstallbin.sh $(INSTALLPERMS) $(BASEDIR) $(SBINDIR) $(LIBDIR) $(VARDIR) $(SPROGS)
	@$(SHELL) $(srcdir)/script/uninstallbin.sh $(INSTALLPERMS) $(BASEDIR) $(BINDIR) $(LIBDIR) $(VARDIR) $(PROGS)

uninstallscripts:
	@$(SHELL) $(srcdir)/script/uninstallscripts.sh $(INSTALLPERMS) $(BINDIR) $(SCRIPTS)

uninstallcp:
	@$(SHELL) $(srcdir)/script/uninstallcp.sh $(CODEPAGEDIR) $(CODEPAGELIST)

clean: 
	-rm -f core */*~ *~ */*.o */*.po */*.po32 */*.so

proto: 
	@echo rebuilding include/proto.h
	@cd $(srcdir) && $(AWK) -f script/mkproto.awk `echo $(PROTO_OBJ) | tr ' ' '\n' | sed -e 's/\.o/\.c/g' | sort -u | egrep -v 'ubiqx/|wrapped'` > include/proto.h

etags:
	etags `find . -name "*.[ch]"`

ctags:
	ctags `find . -name "*.[ch]"`

realclean: clean
	-rm -f config.log $(PROGS)
	-rmdir bin

distclean: realclean
	-rm -f include/config.h include/stamp-h Makefile
	-rm -f config.status config.cache so_locations
	-rm -rf .deps
