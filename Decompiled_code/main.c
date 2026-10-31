//This is a decompiled code , it is non-executable and will show error if put in use without setup.
int main(int argc,char **argv)

{
  int is_redirected;
  FILE *_File;
  undefined8 uVar1;
  HMODULE hModule;
  int *p_argc;
  undefined *puVar2;
  char *msg;
  char **ppcVar3;
  longlong lVar4;
  int arg_idx;
  undefined8 in_R9;
  int remaining_argc [2];
  char *pFilePart;
  char target_path [260];
  char search_pattern [260];
  bool has_file_arg;
  
  has_file_arg = false;
  remaining_argc[0] = argc;
  is_redirected = IsConsoleRedirected();
  if (is_redirected != 0) {
    g_is_stdout_redirected = 1;
    _File = (FILE *)__acrt_iob_func(1);
    in_R9 = 0;
    setvbuf(_File,(char *)0x0,4,0);
  }
  PrintBanner("Strings",remaining_argc,argv);
  p_argc = remaining_argc;
  ppcVar3 = argv;
  is_redirected = CheckEulaAgreement("Strings",p_argc,argv);
  if (is_redirected == 0) {
    return 1;
  }
  if (remaining_argc[0] < 2) {
    uVar1 = print_usage(*argv,p_argc,ppcVar3,in_R9);
    return (int)uVar1;
  }
  arg_idx = 1;
  if (1 < remaining_argc[0]) {
    lVar4 = 1;
    ppcVar3 = argv + 2;
    do {
      is_redirected = _stricmp((uchar *)argv[lVar4],"/s");
      if ((is_redirected == 0) ||
         (is_redirected = _stricmp((uchar *)argv[lVar4],"-s"), is_redirected == 0)) {
        g_recurse_subdirectories = 1;
      }
      else {
        is_redirected = _stricmp((uchar *)argv[lVar4],"/a");
        if ((is_redirected == 0) ||
           (is_redirected = _stricmp((uchar *)argv[lVar4],"-a"), is_redirected == 0)) {
          g_scan_ascii = '\x01';
        }
        else {
          is_redirected = _stricmp((uchar *)argv[lVar4],"/o");
          if ((is_redirected == 0) ||
             (is_redirected = _stricmp((uchar *)argv[lVar4],"-o"), is_redirected == 0)) {
            g_print_file_offset = 1;
          }
          else {
            is_redirected = _stricmp((uchar *)argv[lVar4],"/u");
            if ((is_redirected == 0) ||
               (is_redirected = _stricmp((uchar *)argv[lVar4],"-u"), is_redirected == 0)) {
              g_scan_unicode = '\x01';
            }
            else {
              puVar2 = &DAT_14005ae10;
              is_redirected = _stricmp((uchar *)argv[lVar4],"/b");
              if (is_redirected != 0) {
                puVar2 = &DAT_14005ae14;
                is_redirected = _stricmp((uchar *)argv[lVar4],"-b");
                if (is_redirected != 0) {
                  puVar2 = &DAT_14005ae18;
                  is_redirected = _stricmp((uchar *)argv[lVar4],"/f");
                  if (is_redirected != 0) {
                    puVar2 = &DAT_14005ae1c;
                    is_redirected = _stricmp((uchar *)argv[lVar4],"-f");
                    if (is_redirected != 0) {
                      puVar2 = &DAT_14005ae20;
                      is_redirected = _stricmp((uchar *)argv[lVar4],"/n");
                      if (is_redirected != 0) {
                        puVar2 = &DAT_14005ae24;
                        is_redirected = _stricmp((uchar *)argv[lVar4],"-n");
                        if (is_redirected != 0) {
                          puVar2 = &DAT_14005ae28;
                          is_redirected = _stricmp((uchar *)argv[lVar4],"/?");
                          if (is_redirected == 0) goto LAB_140004257;
                          puVar2 = &DAT_14005ae2c;
                          is_redirected = _stricmp((uchar *)argv[lVar4],"-?");
                          if ((is_redirected == 0) || (has_file_arg)) goto LAB_140004257;
                          has_file_arg = true;
                          goto LAB_1400041fd;
                        }
                      }
                      if (remaining_argc[0] < 3) goto LAB_140004257;
                      lVar4 = lVar4 + 1;
                      g_min_string_length = atoi(*ppcVar3);
                      if (g_min_string_length == 0) goto LAB_140004257;
                      arg_idx = arg_idx + 1;
                      ppcVar3 = ppcVar3 + 1;
                      goto LAB_1400041fd;
                    }
                  }
                  if (remaining_argc[0] < 3) goto LAB_140004257;
                  lVar4 = lVar4 + 1;
                  is_redirected = atoi(*ppcVar3);
                  g_file_starting_offset = (longlong)is_redirected;
                  if (is_redirected == 0) goto LAB_140004257;
                  arg_idx = arg_idx + 1;
                  ppcVar3 = ppcVar3 + 1;
                  goto LAB_1400041fd;
                }
              }
              if (remaining_argc[0] < 3) {
LAB_140004257:
                is_redirected = print_usage(*argv,puVar2);
                return is_redirected;
              }
              lVar4 = lVar4 + 1;
              is_redirected = atoi(*ppcVar3);
              g_bytes_to_scan = (longlong)is_redirected;
              if (is_redirected == 0) goto LAB_140004257;
              arg_idx = arg_idx + 1;
              ppcVar3 = ppcVar3 + 1;
            }
          }
        }
      }
LAB_1400041fd:
      arg_idx = arg_idx + 1;
      lVar4 = lVar4 + 1;
      ppcVar3 = ppcVar3 + 1;
    } while (arg_idx < remaining_argc[0]);
  }
  if ((g_scan_ascii == '\0') && (g_scan_unicode == '\0')) {
    g_scan_unicode = '\x01';
    g_scan_ascii = '\x01';
  }
  if (has_file_arg) {
    GetFullPathNameA(argv[remaining_argc[0] + -1],0x104,target_path,&pFilePart);
  }
  else {
    GetCurrentDirectoryA(0x104,target_path);
  }
  hModule = GetModuleHandleA("user32.dll");
  _pfn_IsCharAlphaNumericW = GetProcAddress(hModule,"IsCharAlphaNumericW");
  scan_directory_or_file(target_path,search_pattern);
  if (g_matching_files_count == 0) {
    puVar2 = __acrt_iob_func(2);
    msg = "No matching files were found.\n\n";
  }
  else {
    if (g_strings_found_flag != '\0') {
      return 0;
    }
    puVar2 = __acrt_iob_func(2);
    msg = "No strings found.\n\n";
  }
  PrintStderr(puVar2,msg);
  return 0;
}

