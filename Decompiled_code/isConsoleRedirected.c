//This is a decompiled code , it is non-executable and will show error if put in use without setup.

int IsConsoleRedirected(void)

{
  DWORD dwFileType;
  HANDLE hFile;
  
  hFile = GetStdHandle(STD_OUTPUT_HANDLE);
  dwFileType = GetFileType(hFile);
  return (uint)(dwFileType == FILE_TYPE_PIPE);
}

