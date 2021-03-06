kdb-file(1) -- Displays which file a key is stored in
=====================================================

## SYNOPSIS

`kdb file <path>`  

Where `path` is the path of a key.  

## DESCRIPTION

This command prints which file a given key is stored in.  
While many keys are stored in a default key database file, many others are stored in any number of configuration files located all over the system.  
This tool is made to allow users to find out the file that a key is actually stored in.  
This command makes use of Elektra's `resolver` plugin which the uer can learn more about by running the command `kdb info resolver`.

## OPTIONS

- `-H`, `--help`:
  Show the man page.
- `-V`, `--version`:
  Print version info.
- `-n`, `--no-newline`:
  Suppress the newline at the end of the output.
- `-N`, `--namespace ns`:
  Specify the namespace to use when writing cascading keys.
  Default: value of `/sw/kdb/current/namespace` or user.

## KDB

- `/sw/kdb/current/namespace`:
  Specifies which default namespace should be used when setting a cascading name.
  Note, that as root you can set `user/sw/kdb/current/namespace` to `system` to
  get the expected default.
  (by default the namespace is user)



## EXAMPLES

To find which file a key is stored in:  
	`kdb file user/example/key`  

## SEE ALSO

- [elektra-mounting(7)](elektra-mounting.md)
- [elektra-namespaces(7)](elektra-namespaces.md)
