/* 
 * File:   event.h
 * Author: andrey5
 *
 * Created on 19 Август 2011 г., 4:23
 */

#ifndef EVENT_H
#define	EVENT_H

#ifdef	__cplusplus
extern "C" {
#endif

// create
// add
// del
// wait
// callback
    
typedef unsigned int p_event_t;
typedef int p_event_err_t;

// дескриптор
typedef struct p_event_info_o {
    p_event_t event;
    unsigned int size;
    unsigned short type = 0;// тип 
} p_event_info_o;

// набор параметров в add/del
typedef struct p_event_arg_o {
    unsigned int listenfd;
    unsigned int events;
} p_event_arg_o;

/*
 * 
 */
extern p_event_err_t p_event_create(p_event_info_o *info, unsigned int size);

/*
 * 
 */
extern p_event_err_t p_event_add(p_event_info_o *info, p_event_arg_o *event);

/*
 * 
 */
extern p_event_err_t p_event_del(p_event_info_o *info, p_event_arg_o *event);

/*
 * 
 */
extern p_event_err_t p_event_wait(p_event_info_o *info);

/*
 * 
 */
extern p_event_err_t p_event_current(p_event_info_o *info);

/*
 * 
 */
extern p_event_err_t p_event_destroy(p_event_info_o *info);



#ifdef	__cplusplus
}
#endif

#endif	/* EVENT_H */

