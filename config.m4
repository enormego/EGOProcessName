dnl config.m4 for extension egoprocessname

PHP_ARG_ENABLE(egoprocessname, whether to enable egoprocessname support,
[  --enable-egoprocessname           Enable egoprocessname support])

if test "$PHP_EGOPROCESSNAME" != "no"; then
  PHP_NEW_EXTENSION(egoprocessname, ego_process_name.c, $ext_shared)
fi

