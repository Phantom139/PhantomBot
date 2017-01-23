/**
    include.h
    PhantomBot Project
    By: Robert F. (Phantom139)
**/

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <thread>
#include <chrono>

//Files needed by ALL other files
#include "Lib/exception.h"
#include "Lib/mSingleton.h"

using namespace std;
