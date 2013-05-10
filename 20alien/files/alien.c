/* This file has been generated by the Hex-Rays decompiler.
   Copyright (c) 2009 Hex-Rays <info@hex-rays.com>

   Detected compiler: GNU C++
*/

#include <defs.h>


//-------------------------------------------------------------------------
// Data declarations

extern _UNKNOWN loc_8048146; // weak
extern char byte_8048148[]; // weak

//-------------------------------------------------------------------------
// Function declarations

void __cdecl start(char a1, int a2);


//----- (080480B8) --------------------------------------------------------
//a1 unused, so we assume a2 = input
void __cdecl start(char a1, int a2)
{
  //registers http://www.codeguru.com/cpp/cpp/cpp_mfc/tutorials/article.php/c9415/An-Introduction-to-Assembly-Language-Part-II.htm
  unsigned int v4; // edx@4
  int v3; // edi@3
  int v2; // ebx@1
  int v5; // ecx@9
  int v6; // eax@13
  unsigned int v7; // [sp+4h] [bp-18h]@3
  void *v8; // [sp+20h] [bp+4h]@2

  v2 = 0;
  //These 2 first ifs are to protect against ptrace and debuggers. Smart!
  if ( sys_ptrace(v2, 0, (void *)v2, 0) ) //http://lwn.net/Articles/146973/
    goto LABEL_17;
  if ( v8 != (void *)2 ) //Used for many things, one of them "Breakout switch on hardware debuggers" http://www.cs.cmu.edu/~ralf/files.html
    goto LABEL_17;
  v3 = a2;
  v7 = 1337;
  while ( 1 )
  {
    v5 = *(_BYTE *)v3;
    if ( !(_BYTE)v5 )
      break;
    v4 = 16807 * v7 % 0x7FFFFFF;
    v7 = 16807 * v7 % 0x7FFFFFF;
    if ( (unsigned int)(v3 - a2) > 0x1C || ((unsigned __int8)v4 ^ v5) != (unsigned __int8)byte_8048148[v3 - a2] )
      v2 = -1;
    ++v3;
  }
  if ( (unsigned int)(v3 - a2) <= 0x1C )
LABEL_17:
    v2 = -1;
  v6 = sys_exit(v2);
  JUMPOUT(loc_8048146);
}

// ALL OK, 1 function(s) have been successfully decompiled
