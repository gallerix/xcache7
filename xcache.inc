<?php
// Avoid redeclare
define('XCACHED', true);

// Directory to save files, php need permission to write
$xdir='/var/xcache/';

function xcache_set($key, $val){
    global $xdir;
    $key=strtr(trim($key), [' '=>'_', '#'=>'', '/'=>'--', '.'=>'']);
    $f=$xdir.substr($key,0,1);
    if(!is_dir($f)) mkdir($f);
    $val=var_export($val, true);
    // Uncoment if you wish to use it for object store
    //$val=str_replace('stdClass::__set_state', '(object)', $val);
    file_put_contents($f.'/'.$key.'.inc', '<?php $val='."$val;\r\n", LOCK_EX);
}

function xcache_isset($key){
    global $xdir;
    $key=strtr(trim($key), [' '=>'-', '#'=>'', '/'=>'--', '.'=>'']);
    $f=$xdir.substr($key,0,1);
    return is_file($f.'/'.$key.'.inc')? filemtime($f.'/'.$key.'.inc'):false;
}

function xcache_get($key, $Revalidate=false){
    global $xdir;
    $key=strtr(trim($key), [' '=>'-', '#'=>'', '/'=>'--', '.'=>'']);
    $f=$xdir.substr($key,0,1);
    if(!$Revalidate) @include $f.'/'.$key.'.inc';
    else eval('?>'.file_get_contents($f.'/'.$key.'.inc'));
    return isset($val)? $val:false;
}

function xcache_unset($key){
    global $xdir;
    $key=strtr(trim($key), [' '=>'-', '#'=>'', '/'=>'--', '.'=>'']);
    $f=$xdir.substr($key,0,1);
    unlink($f.'/'.$key.'.inc');
}

function xcache_unset_by_prefix($key){
    global $xdir;
    $key=strtr(trim($key), [' '=>'-', '#'=>'', '/'=>'--', '.'=>'']);
    $f=$xdir.substr($key,0,1);
    exec('rm -rf '.$f.'/'.$key.'*');
}
