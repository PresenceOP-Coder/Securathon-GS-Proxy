//This is a decompiled code , it is non-executable and will show error if put in use without setup.

int CheckEulaAgreement(char *app_name,int *p_argc,char **argv)

{
  int eula_accepted;
  HMODULE hModule;
  void *pfn_CommandLineToArgvW;
  LPWSTR cmdline;
  wchar_t **wide_argv;
  int cur_argc;
  int shift_idx;
  char **p_argv_shift;
  wchar_t **p_wide_shift;
  uint accepted;
  longlong arg_idx;
  
  arg_idx = 0;
  eula_accepted = 0;
  if ((p_argc == (int *)0x0) || (argv == (char **)0x0)) {
    accepted = 0;
    hModule = LoadLibraryWrapper("Shell32.dll",1);
    pfn_CommandLineToArgvW = GetProcAddress(hModule,"CommandLineToArgvW");
    if (pfn_CommandLineToArgvW != (void *)0x0) {
      cmdline = GetCommandLineW();
      wide_argv = (wchar_t **)(*pfn_CommandLineToArgvW)(cmdline,&g_wide_argc);
      eula_accepted = 0;
      if (0 < g_wide_argc) {
LAB_140002290:
        p_wide_shift = wide_argv + arg_idx;
        shift_idx = _wcsicmp(wide_argv[arg_idx],L"/accepteula");
        if ((shift_idx != 0) && (shift_idx = _wcsicmp(*p_wide_shift,L"-accepteula"), shift_idx != 0)
           ) goto code_r0x0001400022bb;
        accepted = 1;
        if (eula_accepted < g_wide_argc + -1) {
          do {
            eula_accepted = eula_accepted + 1;
            *p_wide_shift = p_wide_shift[1];
            p_wide_shift = p_wide_shift + 1;
          } while (eula_accepted < g_wide_argc + -1);
        }
        g_wide_argc = g_wide_argc + -1;
      }
    }
LAB_140002302:
    eula_accepted = ShowOrVerifyEulaRegistry(app_name,accepted);
    if (eula_accepted != 0) {
      accepted = 1;
    }
  }
  else {
    shift_idx = 0;
    if (0 < *p_argc) {
      arg_idx = 0;
LAB_1400021b0:
      p_argv_shift = argv + arg_idx;
      eula_accepted = _stricmp((uchar *)argv[arg_idx],(uchar *)"/accepteula");
      if ((eula_accepted != 0) &&
         (eula_accepted = _stricmp((uchar *)*p_argv_shift,(uchar *)"-accepteula"),
         eula_accepted != 0)) goto code_r0x0001400021db;
      cur_argc = *p_argc;
      eula_accepted = 1;
      if (shift_idx < cur_argc + -1) {
        do {
          shift_idx = shift_idx + 1;
          *p_argv_shift = p_argv_shift[1];
          p_argv_shift = p_argv_shift + 1;
          cur_argc = *p_argc;
        } while (shift_idx < cur_argc + -1);
      }
      *p_argc = cur_argc + -1;
    }
LAB_14000221d:
    shift_idx = ShowOrVerifyEulaRegistry(app_name,eula_accepted);
    if (shift_idx != 0) {
      eula_accepted = 1;
    }
    accepted = (uint)(eula_accepted != 0);
  }
  return accepted;
code_r0x0001400022bb:
  eula_accepted = eula_accepted + 1;
  arg_idx = arg_idx + 1;
  accepted = 0;
  if (g_wide_argc <= eula_accepted) goto LAB_140002302;
  goto LAB_140002290;
code_r0x0001400021db:
  shift_idx = shift_idx + 1;
  arg_idx = arg_idx + 1;
  eula_accepted = 0;
  if (*p_argc <= shift_idx) goto LAB_14000221d;
  goto LAB_1400021b0;
}

//Function associated to this code: ShowOrVerifyEulaRegistry