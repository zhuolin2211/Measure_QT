#ifndef PLATFORM_CONFIG_H
#define PLATFORM_CONFIG_H
#define RASPBERRY_PI    0
#define WINDOWS 1


#if WINDOWS
#define database_file "H:/mydatabase.sqlite"
#endif
#if RASPBERRY_PI
#define database_file "/home/pi/DataBase/mydatabase.sqlite"
#endif

#endif // PLATFORM_CONFIG_H
