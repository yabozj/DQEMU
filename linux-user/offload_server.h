#ifndef OFFLOAD_SERVER_H
#define OFFLOAD_SERVER_H


#include "qemu/osdep.h"
#include "qemu/units.h"
#include "qemu-version.h"
#include <sys/syscall.h>
#include <sys/resource.h>

#include "qapi/error.h"
#include "qemu.h"
#include "qemu/path.h"
#include "qemu/config-file.h"
#include "qemu/cutils.h"
#include "qemu/help_option.h"
#include "cpu.h"
#include "exec/exec-all.h"
#include "tcg.h"
#include "qemu/timer.h"
#include "qemu/envlist.h"
#include "elf.h"
#include "trace/control.h"
#include "target_elf.h"
#include "cpu_loop-common.h"

#include <sys/socket.h>
#include "offload_common.h"
#include <sys/timeb.h>
#define MAP_PAGE_BITS 12
void offload_send_page_request_and_wait(target_ulong page_addr, int perm);
void* offload_server_start_thread(void* arg);

/* Wake up main exec thread. */
extern pthread_mutex_t main_exec_mutex;
extern pthread_cond_t main_exec_cond;
extern int main_exec_flag;
void offload_page_recv_wake_up_thread(target_ulong page_addr, int perm);
static void try_recv(int);
int sktfd;
int client_socket;
extern int offload_server_idx;
static char net_buffer[NET_BUFFER_SIZE];
static pthread_mutex_t socket_mutex;
#define BUFFER_PAYLOAD_P (net_buffer + TCP_HEADER_SIZE)
extern CPUArchState *env;
target_ulong stack_end, stack_start;
extern pthread_mutex_t cmpxchg_mutex;
extern __thread int offload_thread_idx;
int futex_result;
static int autoSend(int,char*,int,int);
static void offload_server_init(void);
static void offload_server_daemonize(void);
static void offload_process_start(void);
static void load_cpu(void);
static void load_binary(void);
static void load_brk(void);
static void load_memory_region(void);
void exec_func(void);
// static void offload_server_process_futex_wait_result(void);
static void offload_process_fork_info(void);

int offload_server_futex_wait(target_ulong uaddr, int op, int val, target_ulong timeout, target_ulong uaddr2, int val3);
static void offload_server_send_page_request(target_ulong page_addr, target_ulong perm);
int offload_segfault_handler_positive(target_ulong page_addr, int perm);
void offload_server_send_mutex_request(target_ulong mutex_addr, target_ulong, target_ulong);
static void offload_process_page_request(void);
static void offload_process_page_content(void);
static void offload_send_page_content(target_ulong page_addr, target_ulong perm,target_long);
static void offload_send_page_ack(target_ulong page_addr, target_ulong perm);
int offload_segfault_handler(int host_signum, siginfo_t *pinfo, void *puc);
static void offload_process_page_perm(void);
void offload_server_start(void);
void* offload_center_server_start(void*);
// static void offload_server_process_futex_wake_result(void);
void offload_server_send_cmpxchg_start(target_ulong, target_ulong, target_ulong);
void offload_server_send_cmpxchg_end(target_ulong, target_ulong);
extern void offload_server_qemu_init(void);
extern void offload_server_extra_init(void);
target_long pass_syscall(void *cpu_env, int num, target_long arg1,
					  target_long arg2, target_long arg3, target_long arg4,
					  target_long arg5, target_long arg6, target_long arg7,
					  target_long arg8);
int offload_server_futex_wake(target_ulong uaddr, int op, int val, target_ulong timeout, target_ulong uaddr2, int val3);
static void offload_server_process_syscall_result(void);
static void offload_process_tid(void);
extern void fork_start(void);
extern void fork_end(int);
extern void start_exclusive(void);
extern void end_exclusive(void);
static void offload_server_process_fs_page(void);
static void offload_server_process_page_wakeup(void);

#ifndef TARGET_AARCH64
PageMapDesc_server page_map_table_s[L1_MAP_TABLE_SIZE][L2_MAP_TABLE_SIZE] __attribute__ ((section (".page_table_section_server"))) __attribute__ ((aligned(4096))) = {0};
#else
PageTable_s *page_map_table_s = NULL;
#endif
PageMapDesc_server *get_pmd_s(target_ulong page_addr);

#endif
