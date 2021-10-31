#ifndef FOREACH_H
#define FOREACH_H

#ifndef ARRAY_LENGTH
#define ARRAY_LENGTH(array) ((sizeof((array)) / sizeof((array)[0])) / ((size_t)(!(sizeof((array)) % sizeof((array)[0])))))
#endif

#ifndef foreach
#define foreach(name, array)    for (int (__ ## array ## _ ## indexer__) = 0, (__ ## array ## _ ## run_once__) = 1; ( __ ## array ## _ ## indexer__) < ARRAY_LENGTH(array) && (__ ## array ## _ ## run_once__); ++(__ ## array ## _ ## indexer__), (__ ## array ## _ ## run_once__) = !(__ ## array ## _ ## run_once__)) \
                                for (typeof(array[0]) name = array[(__ ## array ## _ ## indexer__)]; (__ ## array ## _ ## run_once__); (__ ## array ## _ ## run_once__) = !(__ ## array ## _ ## run_once__))
#endif

#endif