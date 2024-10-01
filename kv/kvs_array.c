#include "kvstore.h"
//singleton
kvs_array_t global_array = {0};
int kvs_array_create(kvs_array_t *inst){
    if (!inst) return -1;
    if (inst->table) return -1;
    if (inst->table){
        printf("table has alloc \n");
        return -1;
    }
    inst->table = kvs_malloc(KVS_ARRAY_SIZE *sizeof(kvs_array_item_t));
    if (!inst->table){
        return -1;
    }
    inst->idx = 0;
    inst->total = 0;
    return 0;
}

void kvs_array_destory(kvs_array_t *inst){
    if (!inst) return;
    if (inst->table){
        kvs_free(inst->table);
    }
}

int kvs_array_set(kvs_array_t *inst, char *key, char *value) {

	if (inst == NULL || key == NULL || value == NULL) return -1;
	if (inst->total == KVS_ARRAY_SIZE) return -1;

	char *str = kvs_array_get(inst, key);
	if (str) {
		return 1; // 
	}

	char *kcopy = kvs_malloc(strlen(key) + 1);
	if (kcopy == NULL) return -2;
	memset(kcopy, 0, strlen(key) + 1);
	strncpy(kcopy, key, strlen(key));

	char *kvalue = kvs_malloc(strlen(value) + 1);
	if (kvalue == NULL) return -2;
	memset(kvalue, 0, strlen(value) + 1);
	strncpy(kvalue, value, strlen(value));

	int i = 0;
	for (i = 0;i < inst->total;i ++) {
		if (inst->table[i].key == NULL) {
			
			inst->table[i].key = kcopy;
			inst->table[i].value = kvalue;
			inst->total ++;
			
			return 0;
		}
	}

	if (i == inst->total && i < KVS_ARRAY_SIZE) {

		inst->table[i].key = kcopy;
		inst->table[i].value = kvalue;
		inst->total ++;
	}

	return 0;
}

char* kvs_array_get(kvs_array_t *inst, char *key) {

	if (inst == NULL || key == NULL) return NULL;

	int i = 0;
	for (i = 0;i < inst->total;i ++) {
		if (inst->table[i].key == NULL) {
			continue;
		}

		if (strcmp(inst->table[i].key, key) == 0) {
			return inst->table[i].value;
		}
	}

	return NULL;
}


/*
 * @return < 0, error;  =0,  success; >0, no exist
 */

int kvs_array_del(kvs_array_t *inst, char *key) {

	if (inst == NULL || key == NULL) return -1;

	int i = 0;
	for (i = 0;i < inst->total;i ++) {

		if (strcmp(inst->table[i].key, key) == 0) {

			kvs_free(inst->table[i].key);
			inst->table[i].key = NULL;

			kvs_free(inst->table[i].value);
			inst->table[i].value = NULL;
// error: > 1024
			if (inst->total-1 == i) {
				inst->total --;
			}
			

			return 0;
		}
	}

	return i;
}


/*
 * @return : < 0, error; =0, success; >0, no exist 
 */

int kvs_array_mod(kvs_array_t *inst, char *key, char *value) {

	if (inst == NULL || key == NULL || value == NULL) return -1;
// error: > 1024
	if (inst->total == 0) {
		return KVS_ARRAY_SIZE;
	}
	

	int i = 0;
	for (i = 0;i < inst->total;i ++) {

		if (inst->table[i].key == NULL) {
			continue;
		}

		if (strcmp(inst->table[i].key, key) == 0) {

			kvs_free(inst->table[i].value);

			char *kvalue = kvs_malloc(strlen(value) + 1);
			if (kvalue == NULL) return -2;
			memset(kvalue, 0, strlen(value) + 1);
			strncpy(kvalue, value, strlen(value));

			inst->table[i].value = kvalue;

			return 0;
		}

	}

	return i;
}


/*
 * @return 0: exist, 1: no exist
 */
int kvs_array_exist(kvs_array_t *inst, char *key) {

	if (!inst || !key) return -1;
	
	char *str = kvs_array_get(inst, key);
	if (!str) {
		return 1; // 
	}
	return 0;
}

