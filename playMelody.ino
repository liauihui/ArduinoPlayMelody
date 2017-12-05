#include <SoftwareSerial.h>

int pnPlay=8;

const String csDo="Do";
const String csRe="Re";
const String csMi="Mi";
const String csFa="Fa";
const String csSo="So";
const String csLa="La";
const String csSi="Si";
const String csRest="Rest";  // rest

const double hzBaseDo=262;   //base frequency; 
const double hzBaseRe=294;
const double hzBaseMi=330;
const double hzBaseFa=349;
const double hzBaseSo=392;
const double hzBaseLa=440;
const double hzBaseSi=494;

class CNote {
  
  public:
  //CNote();

  CNote(const double& pitchmodulation,   //#,b, 2
        const String& basename,          // Do Re Mi Fa ...
        const double& howlong            // seconds
        );
    
  String baseName=csLa;       // la si do re 
  double pitchModulation=1; // pitchx2 upper an octave, pitch/2 lower an octave
  double seconds=2;   // 1 second
  void playNote( const CNote& note);
  
};
//------------------

CNote::CNote( 
    const double& pitchmodulation, 
    const String& basename, 
    const double& howlong) 
{
  this->baseName=basename;   
  this->pitchModulation=pitchmodulation;
  this->seconds=howlong;
}
//-----------------------------------
bool RunSingleNote( const CNote& note)
{
  int duration=note.seconds*1000;  // miliseconds=1000*seconds
  if( csRest == note.baseName ){   // REST
    delay( duration );   
    return; 
  }

  double dHz=hzBaseDo;
  if( csDo == note.baseName ) {
    dHz=hzBaseDo;
  }
  else if( csRe == note.baseName ) {
    dHz=hzBaseRe;
  }
  else if( csMi == note.baseName ) {
    dHz=hzBaseMi;
  }
  else if( csFa == note.baseName ) {
    dHz=hzBaseFa;
  }
  else if( csSo == note.baseName ) {
    dHz=hzBaseSo;
  }
  else if( csLa == note.baseName ) {
    dHz=hzBaseLa;
  }
  else if( csSi == note.baseName ) {
    dHz=hzBaseSi;
  }
  else {
    Serial.println( String("unknown note:")+String(note.baseName) );
    return false; 
  }

  int pitch=dHz*note.pitchModulation;  
  tone(pnPlay,pitch,duration);

  Serial.println( 
     String(" ")+
     String(note.pitchModulation)+
     String(" base=")+
     String(note.baseName)+
     String(" baseHz=")+
     String(dHz)+
     String(" pitch=")+
     String(pitch)+
     String(" duration=")+
     String(duration)
  );
  
  return true; 
}
//---------------

class CNote notes[]=
{
  CNote(1, csDo, 1),  // notes for play 
  CNote(1, csDo, 1),
  CNote(1, csMi, 1),
  CNote(1, csMi, 1),
  CNote(1, csSo, 1),
  CNote(1, csSo, 1),
  CNote(1, csMi, 4),
  CNote(1, csFa, 1),
  CNote(1, csFa, 1),
  CNote(1, csRe, 1),
  CNote(1, csRe, 1),
  CNote(0.5, csSi,  2),
  CNote(0.5, csSi,  2),
  CNote(0.5, csSo,  4),
 
};

//-----------------------------------------
void PlayMelody()
{
  int iSize=sizeof(notes)/sizeof( notes[0] );
  Serial.println( String("number of notes=")+String(iSize) );
  
  for( int x=0; x < iSize; x++ ) { 
    RunSingleNote(notes[x]);
    delay(1000);
  }
  
}
//-------------------------------

void setup() {
  
  Serial.begin(9600);
  pinMode(pnPlay,OUTPUT);
  
}
//=====================================

void loop() {
  
  PlayMelody();
  delay(5000);
  //while(true) { }
}
