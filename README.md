# xcache7
Storing user variables in memory. XCache functionality with PHP7/OPCache

#### Very simple substitute for old good xcache in PHP7.
Save vars to disk and include as PHP to use OPCache.

1. First, turn on OPCache in php.ini, if not already
2. Second, create directory on disk, put it to variable (global $xdir or directly to functions)
3. Third, include xcache.inc to your project

Include like this:
```
if(!defined('XCACHED')) include 'pathto/xcache.inc';
```
or use *function_exists*.

Now you have compatibility with old xcache, and even better:
- You can use it with CLI/Cron.
- Storing engine is PHP7 native Zend OPCache.
- Your variables set is alive after reboot or apache restart.

OPCache have timestamp revalidation – some user defined timeout before changes take effect. If you use long revalidation time and sometimes you need to get variable directly from disk, use:
```
xcache_get('any_var', true);
```
You dont't need to check if variable exist, if not – *xcache_get* just return false.

*xcache_isset* return file timestamp (variable last modofoed time) as success value.

You may want to clean old data from disk sometimes. Kill all in the xcache folder or do something like this (add php script to crontab):
```
foreach(glob('/var/xcache/*', GLOB_ONLYDIR) as $d) exec("find $d/ -type f -mmin +10080 -delete");
```

Good luck!
