void  mp_init(int max_pool_length, void (*error_callback)());
int   mp_get_length();
int   mp_get_max_length();
void  mp_info();
void  mp_exit();
void *mp_new(int length);