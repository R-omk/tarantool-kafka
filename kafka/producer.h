#ifndef TNT_KAFKA_PRODUCER_H
#define TNT_KAFKA_PRODUCER_H

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <librdkafka/rdkafka.h>

#include <queue.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Producer
 */

typedef struct {
    rd_kafka_t      *rd_producer;
    pthread_t       thread;
    pthread_attr_t  attr;
    int             should_stop;
    pthread_mutex_t lock;
} producer_poller_t;

typedef struct {
    rd_kafka_topic_t **elements;
    int32_t count;
    int32_t capacity;
} producer_topics_t;

producer_topics_t *new_producer_topics(int32_t capacity);

int add_producer_topics(producer_topics_t *topics, rd_kafka_topic_t *element);

rd_kafka_topic_t *find_producer_topic_by_name(producer_topics_t *topics, const char *name);

void destroy_producer_topics(producer_topics_t *topics);

typedef struct {
    rd_kafka_t        *rd_producer;
    producer_topics_t *topics;
    event_queues_t    *event_queues;
    producer_poller_t *poller;
} producer_t;

int lua_producer_tostring(struct lua_State *L);

int lua_producer_msg_delivery_poll(struct lua_State *L);

int lua_producer_poll_logs(struct lua_State *L);

int lua_producer_poll_errors(struct lua_State *L);

int lua_producer_produce(struct lua_State *L);

int lua_producer_close(struct lua_State *L);

int lua_producer_gc(struct lua_State *L);

int lua_create_producer(struct lua_State *L);

#endif //TNT_KAFKA_PRODUCER_H
