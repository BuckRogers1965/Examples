#ifdef __cplusplus
#include <cstdio>
#include <cstdlib>
#include <cstring>
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <assert.h>
#include <ctype.h>

#include "espeak/speak_lib.h"

// JMR got the code from this link:
// http://stackoverflow.com/questions/2661129/espeak-sapi-dll-usage-on-windows?rq=1
// Compile like this: g++ espeak_example.cpp -l espeak

// libespeak-dev: /usr/include/espeak/speak_lib.h
// apt-get install libespeak-dev
// apt-get install libportaudio-dev

// g++ -o mine mine.cpp -lespeak
// g++ -o mine mine.cpp -I/usr/include/espeak/ -lespeak
// gcc -o mine mine.cpp -I/usr/include/espeak/ -lespeak


char voicename[40];
int samplerate;
int quiet = 0;
static char genders[4] = {' ','M','F',' '};

//const char *data_path = "/usr/share/";   // /usr/share/espeak-data/
const char *data_path = NULL;   // use default path for espeak-data


int strrcmp(const char *s, const char *sub)
{
int slen = strlen(s);
int sublen = strlen(sub);
return memcmp(s + slen - sublen, sub, sublen);
}


char * strrcpy(char *dest, const char *source)
{
// Pre assertions
assert(dest != NULL);
assert(source != NULL);
assert(dest != source);

// tk: parentheses
while((*dest++ = *source++))
    ;
return(--dest);
}

const char* GetLanguageVoiceName(const char* pszShortSign)
{
#define LANGUAGE_LENGTH 30
static char szReturnValue[LANGUAGE_LENGTH] ;
memset(szReturnValue, 0, LANGUAGE_LENGTH);

for (int i = 0; pszShortSign[i] != '\0'; ++i)
    szReturnValue[i] = (char) tolower(pszShortSign[i]);

const espeak_VOICE **voices;
espeak_VOICE voice_select;
voices = espeak_ListVoices(NULL);

const espeak_VOICE *v;
for(int ix=0; (v = voices[ix]) != NULL; ix++)
{
    if( !strrcmp( v->languages, szReturnValue) )
    {
        strcpy(szReturnValue, v->name);
        return szReturnValue;
    }
} // End for

strcpy(szReturnValue, "default");
return szReturnValue;
} // End function getvoicename


void ListVoices()
{
const espeak_VOICE **voices;
espeak_VOICE voice_select;
voices = espeak_ListVoices(NULL);

const espeak_VOICE *v;
for(int ix=0; (v = voices[ix]) != NULL; ix++)
{
    printf("Shortsign: %s\n", v->languages);
    printf("age: %d\n", v->age);
    printf("gender: %c\n", genders[v->gender]);
    printf("name: %s\n", v->name);
    printf("\n\n");
} // End for
} // End function getvoicename


int main()
{
printf("Hello World!\n");
const char* szVersionInfo = espeak_Info(NULL);

printf("Espeak version: %s\n", szVersionInfo);
samplerate = espeak_Initialize(AUDIO_OUTPUT_PLAYBACK,0,data_path,0);

strcpy(voicename, "default");
// espeak --voices
strcpy(voicename, "english");
strcpy(voicename, GetLanguageVoiceName("EN"));

if(espeak_SetVoiceByName(voicename) != EE_OK)
{
    printf("Espeak setvoice error...\n");
}

static char word[200] = "Hello World" ;
strcpy(word, "This is a test. Really a test.");
int speed = 120;
int volume = 50; // volume in range 0-100    0=silence
int pitch = 50; //  base pitch, range 0-100.  50=normal

// espeak.cpp 625
espeak_SetParameter(espeakRATE, speed, 0);
espeak_SetParameter(espeakVOLUME,volume,0);
espeak_SetParameter(espeakPITCH,pitch,0);
// espeakRANGE:   pitch range, range 0-100. 0-monotone, 50=normal
// espeakPUNCTUATION:  which punctuation characters to announce:
    // value in espeak_PUNCT_TYPE (none, all, some), 
espeak_VOICE *voice_spec = espeak_GetCurrentVoice();
voice_spec->gender=2; // 0=none 1=male, 2=female,
//voice_spec->age = age;

espeak_SetVoiceByProperties(voice_spec);


espeak_Synth( (char*) word, strlen(word)+1, 0, POS_CHARACTER, 0, espeakCHARS_AUTO, NULL, NULL);
espeak_Synchronize();

strcpy(voicename, GetLanguageVoiceName("EN"));
espeak_SetVoiceByName(voicename);
strcpy(word, "Geany was fragged by GSG9 Googlebot");

espeak_Synth( (char*) word, strlen(word)+1, 0, POS_CHARACTER, 0, espeakCHARS_AUTO, NULL, NULL);
espeak_Synchronize();


espeak_Terminate();
printf("Espeak terminated\n");
return EXIT_SUCCESS; 
}

/*
if(espeak_SetVoiceByName(voicename) != EE_OK)
{
    memset(&voice_select,0,sizeof(voice_select));
    voice_select.languages = voicename;
    if(espeak_SetVoiceByProperties(&voice_select) != EE_OK)
    {
        fprintf(stderr,"%svoice '%s'\n",err_load,voicename);
        exit(2);
    }
}
*/
