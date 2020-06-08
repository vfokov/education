<?php

// autoload_static.php @generated by Composer

namespace Composer\Autoload;

class ComposerStaticInitComposerManager
{
    public static $prefixesPsr0 = array (
        'R' => 
        array (
            'RetailCrm\\' => 
            array (
                0 => __DIR__ . '/..' . '/retailcrm/api-client-php/lib',
            ),
        ),
    );

    public static function getInitializer(ClassLoader $loader)
    {
        return \Closure::bind(function () use ($loader) {
            $loader->prefixesPsr0 = ComposerStaticInitComposerManager::$prefixesPsr0;

        }, null, ClassLoader::class);
    }
}
