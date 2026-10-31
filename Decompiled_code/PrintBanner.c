//This is a decompiled code , it is non-executable and will show error if put in use without setup.

bool PrintBanner(char *appName,int *pArgc,char **argv)

{
  int nobanner_found;
  int check_status;
  int stdout_fd;
  DWORD file_type;
  int pos_status;
  int stdout_fd1;
  int is_redirected;
  DWORD version_size;
  FILE *out_stream;
  HANDLE hFile;
  LPVOID pVersionResource;
  wchar_t *pInternalName;
  wchar_t *pFileVersion;
  int cur_argc;
  int arg_idx;
  longlong lVar1;
  char **p_argv_shift;
  fpos_t file_pos;
  WCHAR module_path [260];
  
  nobanner_found = 0;
  if (1 < *pArgc) {
    arg_idx = 1;
    lVar1 = 1;
LAB_1400010a0:
    p_argv_shift = argv + lVar1;
    nobanner_found = _stricmp((uchar *)argv[lVar1],(uchar *)"/nobanner");
    if ((nobanner_found != 0) &&
       (nobanner_found = _stricmp((uchar *)*p_argv_shift,(uchar *)"-nobanner"), nobanner_found != 0)
       ) goto code_r0x0001400010cb;
    cur_argc = *pArgc;
    nobanner_found = 1;
    if (arg_idx < cur_argc + -1) {
      do {
        arg_idx = arg_idx + 1;
        *p_argv_shift = p_argv_shift[1];
        p_argv_shift = p_argv_shift + 1;
        cur_argc = *pArgc;
      } while (arg_idx < cur_argc + -1);
    }
    *pArgc = cur_argc + -1;
  }
LAB_14000110d:
  check_status = CheckSuppressionOrConfig(appName,pArgc,argv);
  if (check_status == 0) {
    out_stream = (FILE *)__acrt_iob_func(1);
    stdout_fd = _fileno(out_stream);
    hFile = (HANDLE)_get_osfhandle(stdout_fd);
    file_type = GetFileType(hFile);
    if (file_type != 2) {
      out_stream = (FILE *)__acrt_iob_func(1);
      pos_status = fgetpos(out_stream,&file_pos);
      if ((pos_status == 0) && (file_pos == 0)) {
        stdout_fd1 = _fileno(out_stream);
        _setmode(stdout_fd1,0x20000);
        WriteUnicodePrefixOrBOM(out_stream,&k_unicode_bom);
      }
      if (nobanner_found == 0) {
        GetModuleFileNameW((HMODULE)0x0,module_path,0x104);
        version_size = GetFileVersionInfoSizeW(module_path,(LPDWORD)&file_pos);
        pVersionResource = _malloc_base((ulonglong)version_size);
        GetFileVersionInfoW(module_path,0,version_size,pVersionResource);
        pInternalName = GetVersionField(pVersionResource,L"InternalName");
        pFileVersion = GetVersionField(pVersionResource,L"FileVersion");
        GetVersionField(pVersionResource,L"FileDescription");
        GetVersionField(pVersionResource,L"LegalCopyright");
        GetVersionField(pVersionResource,L"CompanyName");
        is_redirected = IsConsoleRedirected();
        if (is_redirected == 0) {
          out_stream = (FILE *)__acrt_iob_func(2);
          PrintFormattedHeader(out_stream,L"\n%s v%s - %s\n%s\n%s\n\n",pInternalName,pFileVersion);
          out_stream = (FILE *)__acrt_iob_func(2);
          fflush(out_stream);
        }
        else {
          out_stream = (FILE *)__acrt_iob_func(1);
          PrintFormattedHeader(out_stream,L"\n%s v%s - %s\n%s\n%s\n\n",pInternalName,pFileVersion);
          out_stream = (FILE *)__acrt_iob_func(1);
          fflush(out_stream);
        }
      }
      goto LAB_1400012d0;
    }
  }
  PrintBannerFallback(nobanner_found);
LAB_1400012d0:
  return nobanner_found == 0;
code_r0x0001400010cb:
  arg_idx = arg_idx + 1;
  lVar1 = lVar1 + 1;
  nobanner_found = 0;
  if (*pArgc <= arg_idx) goto LAB_14000110d;
  goto LAB_1400010a0;
}

