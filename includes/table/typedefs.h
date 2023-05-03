#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include "../../includes/bplustree/map.h"
#include "../../includes/bplustree/multimap.h"
#include "../../includes/queue/MyQueue.h"

using namespace std;
typedef Map<string, string> map_ss;
typedef MMap<string, string> mmap_ss;

typedef Map<string, long> map_sl;
typedef MMap<string, long> mmap_sl;

typedef Map<string, MMap<string, long> > map_smmap;
typedef vector<string> vectorstr;
typedef vector<long> vectorlong;
typedef Queue<string> queuestr;

#endif // TYPEDEFS_H