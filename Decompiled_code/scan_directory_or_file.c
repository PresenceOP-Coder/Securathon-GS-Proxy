//This is a decompiled code , it is non-executable and will show error if put in use without setup.


void scan_directory_or_file(char *base_path,char *file_pattern)

{
  char cVar1;
  int iVar2;
  BOOL BVar3;
  longlong p_slash;
  HANDLE hFind;
  longlong copy_idx;
  LPCSTR lpFileName;
  char *p_src;
  CHAR *p_filename;
  undefined8 in_R8;
  undefined8 in_R9;
  _WIN32_FIND_DATAA find_data;
  char dir_prefix [260];
  char full_file_path [260];
  char find_pattern [260];
  
  if (g_is_initial_scan == '\0') {
    sprintf_s(dir_prefix,"%s\\*.*",base_path);
    sprintf_s(find_pattern,"%s\\%s",base_path,file_pattern);
  }
  else {
    p_src = strchr(base_path,0x2a);
    if (p_src == (char *)0x0) {
      sprintf_s(file_pattern,"*.*",in_R8,in_R9);
      if (g_recurse_subdirectories == '\0') {
        p_src = "%s";
      }
      else {
        g_has_wildcard = 1;
        p_src = "%s\\*.*";
      }
      sprintf_s(dir_prefix,p_src,base_path,in_R9);
      sprintf_s(find_pattern,p_src,base_path,in_R9);
    }
    else {
      g_has_wildcard = 1;
      p_slash = strchr((uchar *)base_path,0x5c);
      if (p_slash == 0) {
        sprintf_s(file_pattern,base_path,in_R8,in_R9);
        p_src = base_path;
        do {
          cVar1 = *p_src;
          p_src[(longlong)(dir_prefix + -(longlong)base_path)] = cVar1;
          p_src = p_src + 1;
        } while (cVar1 != '\0');
        sprintf_s(find_pattern,"%s",base_path,in_R9);
      }
      else {
        p_slash = strchr((uchar *)base_path,0x5c);
        sprintf_s(file_pattern,(char *)(p_slash + 1),in_R8,in_R9);
        p_src = base_path;
        do {
          cVar1 = *p_src;
          p_src[(longlong)(dir_prefix + -(longlong)base_path)] = cVar1;
          p_src = p_src + 1;
        } while (cVar1 != '\0');
        p_slash = strchr((uchar *)dir_prefix,0x5c);
        *(undefined4 *)(p_slash + 1) = 0x2a2e2a;
        sprintf_s(find_pattern,"%s",base_path,in_R9);
      }
    }
  }
  hFind = FindFirstFileA(find_pattern,&find_data);
  if (hFind != (HANDLE)0xffffffffffffffff) {
    do {
      iVar2 = strcmp((uchar *)find_data.cFileName,".");
      if ((iVar2 != 0) && (iVar2 = strcmp((uchar *)find_data.cFileName,".."), iVar2 != 0)) {
        p_slash = 0;
        do {
          p_src = dir_prefix + p_slash;
          full_file_path[p_slash] = *p_src;
          p_slash = p_slash + 1;
        } while (*p_src != '\0');
        p_slash = strchr((uchar *)full_file_path,0x5c);
        if (p_slash == 0) {
          p_slash = 0;
          do {
            cVar1 = find_data.cFileName[p_slash];
            full_file_path[p_slash] = cVar1;
            p_slash = p_slash + 1;
          } while (cVar1 != '\0');
        }
        else {
          p_filename = find_data.cFileName;
          p_slash = strchr((uchar *)full_file_path,0x5c);
          do {
            cVar1 = *p_filename;
            p_filename[p_slash + (1 - (longlong)find_data.cFileName)] = cVar1;
            p_filename = p_filename + 1;
          } while (cVar1 != '\0');
        }
        dump_strings_from_file(&find_data,full_file_path);
      }
      BVar3 = FindNextFileA(hFind,&find_data);
    } while (BVar3 != 0);
    FindClose(hFind);
  }
  if (g_recurse_subdirectories != '\0') {
    if (((g_is_initial_scan == '\0') || (p_slash = strchr((uchar *)dir_prefix,0x5c), p_slash != 0))
       || (p_slash = strchr((uchar *)dir_prefix,0x2a), p_slash == 0)) {
      lpFileName = dir_prefix;
    }
    else {
      lpFileName = "*.*";
    }
    hFind = FindFirstFileA(lpFileName,&find_data);
    if (hFind != (HANDLE)0xffffffffffffffff) {
      g_is_initial_scan = '\0';
      do {
        if (((((byte)find_data.dwFileAttributes & 0x10) != 0) &&
            (iVar2 = strcmp((uchar *)find_data.cFileName,"."), iVar2 != 0)) &&
           (iVar2 = strcmp((uchar *)find_data.cFileName,".."), iVar2 != 0)) {
          p_slash = 0;
          do {
            p_src = dir_prefix + p_slash;
            full_file_path[p_slash] = *p_src;
            p_slash = p_slash + 1;
          } while (*p_src != '\0');
          copy_idx = strchr((uchar *)full_file_path,0x5c);
          p_slash = 0;
          if (copy_idx == 0) {
            do {
              cVar1 = find_data.cFileName[p_slash];
              full_file_path[p_slash] = cVar1;
              p_slash = p_slash + 1;
            } while (cVar1 != '\0');
          }
          else {
            p_filename = find_data.cFileName;
            p_slash = strchr((uchar *)full_file_path,0x5c);
            do {
              cVar1 = *p_filename;
              p_filename[p_slash + (1 - (longlong)find_data.cFileName)] = cVar1;
              p_filename = p_filename + 1;
            } while (cVar1 != '\0');
          }
          scan_directory_or_file(full_file_path,file_pattern);
        }
        BVar3 = FindNextFileA(hFind,&find_data);
      } while (BVar3 != 0);
      FindClose(hFind);
    }
  }
  return;
}

