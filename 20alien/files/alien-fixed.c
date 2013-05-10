void __cdecl start(char a1, char *startpos)
{
  int result; // ebx@1
  char *currpos; // edi@3
  unsigned int v4; // edx@4
  char currchar; // cl@9
  int v6; // eax@13
  unsigned int v7; // [sp+4h] [bp-18h]@3
  void *argc; // [sp+20h] [bp+4h]@2

  result = 0;
  if ( sys_ptrace(result, 0, result, 0) )
    goto LABEL_17;
  if ( argc != 2 )
    goto LABEL_17;
  currpos = startpos;
  v7 = 1337;
  while ( 1 )
  {
    *&currchar = *currpos;
    if ( !currchar )
      break;
    v4 = 16807 * v7 % 0x7FFFFFF;
    v7 = 16807 * v7 % 0x7FFFFFF;
    if ( currpos - startpos > 28 || (v4 ^ *&currchar) != data[currpos - startpos] )
      result = -1;
    ++currpos;
  }
  if ( currpos - startpos <= 28 )
LABEL_17:
    result = -1;
  v6 = sys_exit(result);
  JUMPOUT(loc_8048146);
}
