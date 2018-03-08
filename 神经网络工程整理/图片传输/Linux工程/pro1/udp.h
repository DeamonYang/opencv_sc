#ifndef _UDP_H_
#define _UDP_H_

#ifdef __cplusplus
extern "C"{
#endif
void udp_init(void);
void udp_send(char*buf,int len);
void dup_exit(void);

#ifdef __cplusplus
}
#endif

#endif




