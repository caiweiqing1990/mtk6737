cmd_/home/book/work/XY3701_N0/external/test/pcm_module/n_gsm.o := /home/book/work/XY3701_N0/external/test/pcm_module/../../../prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-gcc -Wp,-MD,/home/book/work/XY3701_N0/external/test/pcm_module/.n_gsm.o.d  -nostdinc -isystem /home/book/work/XY3701_N0/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/../lib/gcc/aarch64-linux-android/4.9/include -I/home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include -Iarch/arm64/include/generated  -I/home/book/work/XY3701_N0/kernel-3.18/include -Iinclude -I/home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I/home/book/work/XY3701_N0/kernel-3.18/include/uapi -Iinclude/generated/uapi -include /home/book/work/XY3701_N0/kernel-3.18/include/linux/kconfig.h    -I/home/book/work/XY3701_N0/external/test/pcm_module -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -std=gnu89 -mgeneral-regs-only -fno-pic -fstack-usage -fno-delete-null-pointer-checks -O2 --param=allow-store-data-races=0 -Werror=frame-larger-than=1 -Wframe-larger-than=1400 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time  -DMODULE -mcmodel=large  -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(n_gsm)"  -D"KBUILD_MODNAME=KBUILD_STR(n_gsm)" -c -o /home/book/work/XY3701_N0/external/test/pcm_module/n_gsm.o /home/book/work/XY3701_N0/external/test/pcm_module/n_gsm.c

source_/home/book/work/XY3701_N0/external/test/pcm_module/n_gsm.o := /home/book/work/XY3701_N0/external/test/pcm_module/n_gsm.c

deps_/home/book/work/XY3701_N0/external/test/pcm_module/n_gsm.o := \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/types.h \
  arch/arm64/include/generated/asm/types.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/types.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/int-ll64.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/int-ll64.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi/asm/bitsperlong.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitsperlong.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/bitsperlong.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/posix_types.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/stddef.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/stddef.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
    $(wildcard include/config/gcov/kernel.h) \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi/asm/posix_types.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/posix_types.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/major.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/errno.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/errno.h \
  arch/arm64/include/generated/asm/errno.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/errno.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/errno-base.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/signal.h \
    $(wildcard include/config/old/sigaction.h) \
    $(wildcard include/config/proc/fs.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/const.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/panic/timeout.h) \
    $(wildcard include/config/ring/buffer.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
  /home/book/work/XY3701_N0/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/lib/gcc/aarch64-linux-android/4.9/include/stdarg.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/linkage.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/stringify.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/linkage.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/bitops.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/bitops.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/barrier.h \
    $(wildcard include/config/smp.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/builtin-__ffs.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/builtin-ffs.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/builtin-__fls.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/builtin-fls.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/ffz.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/fls64.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/find.h \
    $(wildcard include/config/generic/find/first/bit.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/sched.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/hweight.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/arch_hweight.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/const_hweight.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/lock.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/non-atomic.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bitops/le.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi/asm/byteorder.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/byteorder/little_endian.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/byteorder/little_endian.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/swab.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/swab.h \
  arch/arm64/include/generated/asm/swab.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/swab.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/byteorder/generic.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/typecheck.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/printk.h \
    $(wildcard include/config/mt/printk/uart/console.h) \
    $(wildcard include/config/mtk/aee/feature.h) \
    $(wildcard include/config/printk/mt/prefix.h) \
    $(wildcard include/config/mt/eng/build.h) \
    $(wildcard include/config/log/too/much/warning.h) \
    $(wildcard include/config/message/loglevel/default.h) \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
    $(wildcard include/config/lto.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/kern_levels.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/kernel.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/sysinfo.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/cache.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/cachetype.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/cputype.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/dynamic_debug.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/bug.h \
    $(wildcard include/config/generic/bug.h) \
  arch/arm64/include/generated/asm/bug.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/memory.h \
    $(wildcard include/config/arm64/va/bits.h) \
    $(wildcard include/config/compat.h) \
  arch/arm64/include/generated/asm/sizes.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/sizes.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/sizes.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/signal.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi/asm/signal.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/signal.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/signal.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/signal-defs.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi/asm/sigcontext.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi/asm/siginfo.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/siginfo.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/siginfo.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/string.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/string.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/fcntl.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/fcntl.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi/asm/fcntl.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/fcntl.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/prove/rcu.h) \
    $(wildcard include/config/no/hz/common.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/virt/cpu/accounting/native.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/mtk/sched/cmp/tgs.h) \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/disable/cpu/sched/domain/balance.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/mtk/sched/cmp.h) \
    $(wildcard include/config/sched/hmp.h) \
    $(wildcard include/config/sched/hmp/prio/filter.h) \
    $(wildcard include/config/hmp/tracer.h) \
    $(wildcard include/config/mtprof/cputime.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/mt/rt/throttle/mon.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/mt/sched/trace.h) \
    $(wildcard include/config/mt/sched/debug.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/preempt/notifiers.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/tasks/rcu.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/virt/cpu/accounting/gen.h) \
    $(wildcard include/config/swap.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/numa/balancing.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/uprobes.h) \
    $(wildcard include/config/bcache.h) \
    $(wildcard include/config/preempt/monitor.h) \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/irq/time/accounting.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/no/hz/full.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/debug/stack/usage.h) \
    $(wildcard include/config/preempt.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/sched.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/sched/prio.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi/asm/param.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/param.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/capability.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/capability.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/timex.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/timex.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/seqlock.h \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/preempt.h \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/context/tracking.h) \
  arch/arm64/include/generated/asm/preempt.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/preempt.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/thread_info.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/thread_info.h \
    $(wildcard include/config/arm64/64k/pages.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/irqflags.h \
    $(wildcard include/config/mtprof.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/irqflags.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/ptrace.h \
    $(wildcard include/config/cpu/big/endian.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi/asm/ptrace.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/hwcap.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi/asm/hwcap.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/bottom_half.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/preempt_mask.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/spinlock_types.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/spinlock_types.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/lockdep.h \
    $(wildcard include/config/lock/stat.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/rwlock_types.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/spinlock.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/processor.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/fpsimd.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/hw_breakpoint.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/rwlock.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/uninline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/atomic.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/cmpxchg.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/atomic-long.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/math64.h \
    $(wildcard include/config/arch/supports/int128.h) \
  arch/arm64/include/generated/asm/div64.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/div64.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/time64.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/time.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/param.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/timex.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/arch_timer.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/clocksource/arm_arch_timer.h \
    $(wildcard include/config/arm/arch/timer.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/clocksource.h \
    $(wildcard include/config/arch/clocksource/data.h) \
    $(wildcard include/config/clocksource/watchdog.h) \
    $(wildcard include/config/clksrc/of.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/ktime.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/jiffies.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/timekeeping.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/io.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/blk_types.h \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/blk/dev/integrity.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/pgtable.h \
    $(wildcard include/config/transparent/hugepage.h) \
    $(wildcard include/config/have/rcu/table/free.h) \
    $(wildcard include/config/arm64/pgtable/levels.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/proc-fns.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/page.h \
    $(wildcard include/config/have/arch/pfn/valid.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/pgtable-types.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/pgtable-nopud.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/getorder.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/pgtable-hwdef.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/pgtable.h \
    $(wildcard include/config/have/arch/soft/dirty.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/arch/enable/split/pmd/ptlock.h) \
    $(wildcard include/config/have/cmpxchg/double.h) \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/compaction.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/auxvec.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/auxvec.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi/asm/auxvec.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/rbtree.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/spin/on/owner.h) \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/osq_lock.h \
  arch/arm64/include/generated/asm/rwsem.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/rwsem.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/completion.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/wait.h \
  arch/arm64/include/generated/asm/current.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/current.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/wait.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/cpumask.h \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/bitmap.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/guard.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/uprobes.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/page-flags-layout.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/generated/bounds.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/sparsemem.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/mmu.h \
  arch/arm64/include/generated/asm/early_ioremap.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/early_ioremap.h \
    $(wildcard include/config/generic/early/ioremap.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/alternative.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/cpufeature.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/xen/xen.h \
    $(wildcard include/config/xen.h) \
    $(wildcard include/config/xen/dom0.h) \
    $(wildcard include/config/xen/pvh.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/iomap.h \
    $(wildcard include/config/has/ioport/map.h) \
    $(wildcard include/config/pci.h) \
    $(wildcard include/config/generic/iomap.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/pci_iomap.h \
    $(wildcard include/config/no/generic/pci/ioport/map.h) \
    $(wildcard include/config/generic/pci/iomap.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/timex.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/nodemask.h \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/movable/node.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/cputime.h \
  arch/arm64/include/generated/asm/cputime.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/cputime.h \
    $(wildcard include/config/virt/cpu/accounting.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/cputime_jiffies.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/smp.h \
    $(wildcard include/config/profile/cpu.h) \
    $(wildcard include/config/mtk/cpu/hotplug/debug/3.h) \
    $(wildcard include/config/mtk/ram/console.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/smp.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/sem.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/rcupdate.h \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/rcu/stall/common.h) \
    $(wildcard include/config/rcu/user/qs.h) \
    $(wildcard include/config/rcu/nocb/cpu.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/rcu/nocb/cpu/all.h) \
    $(wildcard include/config/no/hz/full/sysidle.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/rcutree.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/sem.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/ipc.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/uidgid.h \
    $(wildcard include/config/user/ns.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/highuid.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/ipc.h \
  arch/arm64/include/generated/asm/ipcbuf.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/ipcbuf.h \
  arch/arm64/include/generated/asm/sembuf.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/sembuf.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/shm.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/shm.h \
  arch/arm64/include/generated/asm/shmbuf.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/shmbuf.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/shmparam.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/shmparam.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/pid.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/pfn.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/percpu.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/percpu.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/topology.h \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/cma.h) \
    $(wildcard include/config/memory/isolation.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/have/memblock/node/map.h) \
    $(wildcard include/config/mtk/memcfg.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/page/extension.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/have/bootmem/info/node.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/notifier.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/mutex.h \
    $(wildcard include/config/mutex/spin/on/owner.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/srcu.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
    $(wildcard include/config/sysfs.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/topology.h \
    $(wildcard include/config/arm/cpu/topology.h) \
    $(wildcard include/config/mtk/cpu/topology.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/topology.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/proportions.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/percpu_counter.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/gfp.h \
    $(wildcard include/config/dmauser/pages.h) \
    $(wildcard include/config/zone/movable/cma.h) \
    $(wildcard include/config/pm/sleep.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
    $(wildcard include/config/have/arch/seccomp/filter.h) \
    $(wildcard include/config/seccomp/filter.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/seccomp.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/seccomp.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/unistd.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi/asm/unistd.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/unistd.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/unistd.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/seccomp.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/unistd.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/rculist.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/resource.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/resource.h \
  arch/arm64/include/generated/asm/resource.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/resource.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/resource.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/timerfd.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/timerqueue.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/latencytop.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
    $(wildcard include/config/security.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/key.h \
    $(wildcard include/config/sysctl.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/sysctl.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/sysctl.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/assoc_array.h \
    $(wildcard include/config/associative/array.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/magic.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/interrupt.h \
    $(wildcard include/config/irq/forced/threading.h) \
    $(wildcard include/config/generic/irq/probe.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/irqreturn.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/irqnr.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/irqnr.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/hardirq.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/vtime.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/context_tracking_state.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/static_key.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/hardirq.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/irq.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/irq.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/irq_cpustat.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/kref.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/tty.h \
    $(wildcard include/config/tty.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/fs.h \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/fs/xip.h) \
    $(wildcard include/config/migration.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/kdev_t.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/kdev_t.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/dcache.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/rculist_bl.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/list_bl.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/bit_spinlock.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/lockref.h \
    $(wildcard include/config/arch/use/cmpxchg/lockref.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/path.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/stat.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/stat.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/uapi/asm/stat.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/stat.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/compat.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/ptrace.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/err.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/pid_namespace.h \
    $(wildcard include/config/pid/ns.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/mm.h \
    $(wildcard include/config/have/arch/mmap/rnd/bits.h) \
    $(wildcard include/config/have/arch/mmap/rnd/compat/bits.h) \
    $(wildcard include/config/mem/soft/dirty.h) \
    $(wildcard include/config/x86.h) \
    $(wildcard include/config/ppc.h) \
    $(wildcard include/config/parisc.h) \
    $(wildcard include/config/metag.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ksm.h) \
    $(wildcard include/config/shmem.h) \
    $(wildcard include/config/debug/vm/rb.h) \
    $(wildcard include/config/debug/pagealloc.h) \
    $(wildcard include/config/hibernation.h) \
    $(wildcard include/config/hugetlbfs.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/range.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/shrinker.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/page_ext.h \
    $(wildcard include/config/page/owner.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/stacktrace.h \
    $(wildcard include/config/stacktrace.h) \
    $(wildcard include/config/user/stacktrace/support.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/page-flags.h \
    $(wildcard include/config/pageflags/extended.h) \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/toi/incremental.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/huge_mm.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
    $(wildcard include/config/debug/tlbflush.h) \
    $(wildcard include/config/debug/vm/vmacache.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/vm_event_item.h \
    $(wildcard include/config/memory/balloon.h) \
    $(wildcard include/config/balloon/compaction.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/nsproxy.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/ptrace.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/stat.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/list_lru.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/radix-tree.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/semaphore.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/fiemap.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/migrate_mode.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/percpu-rwsem.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/fs.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/limits.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/ioctl.h \
  arch/arm64/include/generated/asm/ioctl.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/ioctl.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/ioctl.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/dqblk_xfs.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/dqblk_v1.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/dqblk_v2.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/dqblk_qtree.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/projid.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/quota.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/nfs_fs_i.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/termios.h \
  arch/arm64/include/generated/asm/termios.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/termios.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/uaccess.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/compiler.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/termios.h \
  arch/arm64/include/generated/asm/termbits.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/termbits.h \
  arch/arm64/include/generated/asm/ioctls.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/ioctls.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/tty_driver.h \
    $(wildcard include/config/console/poll.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/cdev.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/kobject.h \
    $(wildcard include/config/uevent/helper.h) \
    $(wildcard include/config/debug/kobject/release.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/sysfs.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/kernfs.h \
    $(wildcard include/config/kernfs.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/idr.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/kobject_ns.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/tty_ldisc.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/tty_flags.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/tty.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/ctype.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/memcg/kmem.h) \
    $(wildcard include/config/slab.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/kmemleak.h \
    $(wildcard include/config/debug/kmemleak.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/poll.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/poll.h \
  arch/arm64/include/generated/asm/poll.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/poll.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/file.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/uaccess.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/module.h \
    $(wildcard include/config/module/sig.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/debug/set/module/ronx.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/kmod.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/elf.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/elf.h \
  arch/arm64/include/generated/asm/user.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/user.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/elf.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/elf-em.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ppc64.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/module.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/module.h \
    $(wildcard include/config/have/mod/arch/specific.h) \
    $(wildcard include/config/modules/use/elf/rel.h) \
    $(wildcard include/config/modules/use/elf/rela.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/tty_flip.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/serial.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/serial.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/kfifo.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/scatterlist.h \
    $(wildcard include/config/debug/sg.h) \
    $(wildcard include/config/arch/has/sg/chain.h) \
  arch/arm64/include/generated/asm/scatterlist.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/scatterlist.h \
    $(wildcard include/config/need/sg/dma/length.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/skbuff.h \
    $(wildcard include/config/nf/conntrack.h) \
    $(wildcard include/config/bridge/netfilter.h) \
    $(wildcard include/config/xfrm.h) \
    $(wildcard include/config/ipv6/ndisc/nodetype.h) \
    $(wildcard include/config/net/sched.h) \
    $(wildcard include/config/net/cls/act.h) \
    $(wildcard include/config/net/rx/busy/poll.h) \
    $(wildcard include/config/network/secmark.h) \
    $(wildcard include/config/network/phy/timestamping.h) \
    $(wildcard include/config/netfilter/xt/target/trace.h) \
    $(wildcard include/config/nf/tables.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/kmemcheck.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/net.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/random.h \
    $(wildcard include/config/arch/random.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/random.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/net.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/socket.h \
  arch/arm64/include/generated/asm/socket.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/socket.h \
  arch/arm64/include/generated/asm/sockios.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/asm-generic/sockios.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/sockios.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/uio.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/uio.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/socket.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/textsearch.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/checksum.h \
  arch/arm64/include/generated/asm/checksum.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/checksum.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/dma-mapping.h \
    $(wildcard include/config/has/dma.h) \
    $(wildcard include/config/arch/has/dma/set/coherent/mask.h) \
    $(wildcard include/config/have/dma/attrs.h) \
    $(wildcard include/config/need/dma/map/state.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/acpi.h) \
    $(wildcard include/config/pinctrl.h) \
    $(wildcard include/config/dma/cma.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/ioport.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/klist.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/pinctrl/devinfo.h \
    $(wildcard include/config/pm.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/pinctrl/consumer.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/seq_file.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/pinctrl/pinctrl-state.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/pm.h \
    $(wildcard include/config/vt/console/sleep.h) \
    $(wildcard include/config/pm/runtime.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/ratelimit.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/device.h \
    $(wildcard include/config/iommu/api.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/pm_wakeup.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/dma-attrs.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/dma-direction.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/dma-mapping.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/vmalloc.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/dma-coherent.h \
    $(wildcard include/config/have/generic/dma/coherent.h) \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/asm/xen/hypervisor.h \
  /home/book/work/XY3701_N0/kernel-3.18/arch/arm64/include/../../arm/include/asm/xen/hypervisor.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/dma-mapping-common.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/dma-debug.h \
    $(wildcard include/config/dma/api/debug.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/netdev_features.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/flow_keys.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/arp.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/if_arp.h \
    $(wildcard include/config/firewire/net.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/if_arp.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/netdevice.h \
    $(wildcard include/config/dcb.h) \
    $(wildcard include/config/wlan.h) \
    $(wildcard include/config/ax25.h) \
    $(wildcard include/config/mac80211/mesh.h) \
    $(wildcard include/config/net/ipip.h) \
    $(wildcard include/config/net/ipgre.h) \
    $(wildcard include/config/ipv6/sit.h) \
    $(wildcard include/config/ipv6/tunnel.h) \
    $(wildcard include/config/rps.h) \
    $(wildcard include/config/netpoll.h) \
    $(wildcard include/config/xps.h) \
    $(wildcard include/config/bql.h) \
    $(wildcard include/config/rfs/accel.h) \
    $(wildcard include/config/fcoe.h) \
    $(wildcard include/config/net/poll/controller.h) \
    $(wildcard include/config/libfcoe.h) \
    $(wildcard include/config/wireless/ext.h) \
    $(wildcard include/config/vlan/8021q.h) \
    $(wildcard include/config/net/dsa.h) \
    $(wildcard include/config/tipc.h) \
    $(wildcard include/config/net/ns.h) \
    $(wildcard include/config/cgroup/net/prio.h) \
    $(wildcard include/config/net/flow/limit.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/pm_qos.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/miscdevice.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/delay.h \
  arch/arm64/include/generated/asm/delay.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/delay.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/prefetch.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/dmaengine.h \
    $(wildcard include/config/async/tx/enable/channel/switch.h) \
    $(wildcard include/config/dma/engine.h) \
    $(wildcard include/config/rapidio/dma/engine.h) \
    $(wildcard include/config/async/tx/dma.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/dynamic_queue_limits.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/ethtool.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/compat.h \
    $(wildcard include/config/compat/old/sigaction.h) \
    $(wildcard include/config/odd/rt/sigaction.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/if.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/hdlc/ioctl.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/aio_abi.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/ethtool.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/if_ether.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/if_ether.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/net_namespace.h \
    $(wildcard include/config/ipv6.h) \
    $(wildcard include/config/ieee802154/6lowpan.h) \
    $(wildcard include/config/ip/sctp.h) \
    $(wildcard include/config/ip/dccp.h) \
    $(wildcard include/config/netfilter.h) \
    $(wildcard include/config/nf/defrag/ipv6.h) \
    $(wildcard include/config/wext/core.h) \
    $(wildcard include/config/ip/vs.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/flow.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/in6.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/in6.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/libc-compat.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/core.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/mib.h \
    $(wildcard include/config/xfrm/statistics.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/snmp.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/snmp.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/u64_stats_sync.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/unix.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/packet.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/ipv4.h \
    $(wildcard include/config/ip/multiple/tables.h) \
    $(wildcard include/config/ip/route/classid.h) \
    $(wildcard include/config/ip/mroute.h) \
    $(wildcard include/config/ip/mroute/multiple/tables.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/inet_frag.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/ipv6.h \
    $(wildcard include/config/ipv6/multiple/tables.h) \
    $(wildcard include/config/ipv6/mroute.h) \
    $(wildcard include/config/ipv6/mroute/multiple/tables.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/dst_ops.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/ieee802154_6lowpan.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/sctp.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/dccp.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/netfilter.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/proc_fs.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/netfilter.h \
    $(wildcard include/config/nf/nat/needed.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/in.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/in.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/netfilter.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/x_tables.h \
    $(wildcard include/config/bridge/nf/ebtables.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/conntrack.h \
    $(wildcard include/config/nf/conntrack/proc/compat.h) \
    $(wildcard include/config/nf/conntrack/events.h) \
    $(wildcard include/config/nf/conntrack/labels.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/list_nulls.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/netfilter/nf_conntrack_tcp.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/netfilter/nf_conntrack_tcp.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/nftables.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netns/xfrm.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/xfrm.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/flowcache.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/seq_file_net.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/dsa.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/of.h \
    $(wildcard include/config/sparc.h) \
    $(wildcard include/config/of/dynamic.h) \
    $(wildcard include/config/of.h) \
    $(wildcard include/config/attach/node.h) \
    $(wildcard include/config/detach/node.h) \
    $(wildcard include/config/add/property.h) \
    $(wildcard include/config/remove/property.h) \
    $(wildcard include/config/update/property.h) \
    $(wildcard include/config/of/resolve.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/mod_devicetable.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/uuid.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/uuid.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/property.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/phy.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/mii.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/mii.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/phy_fixed.h \
    $(wildcard include/config/fixed/phy.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netprio_cgroup.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/cgroup.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/cgroupstats.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/taskstats.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/percpu-refcount.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/cgroup_subsys.h \
    $(wildcard include/config/cgroup/cpuacct.h) \
    $(wildcard include/config/cgroup/device.h) \
    $(wildcard include/config/cgroup/freezer.h) \
    $(wildcard include/config/cgroup/net/classid.h) \
    $(wildcard include/config/cgroup/perf.h) \
    $(wildcard include/config/cgroup/hugetlb.h) \
    $(wildcard include/config/cgroup/debug.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/neighbour.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/netlink.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/scm.h \
    $(wildcard include/config/security/network.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/security.h \
    $(wildcard include/config/fw/loader/user/helper.h) \
    $(wildcard include/config/security/path.h) \
    $(wildcard include/config/security/network/xfrm.h) \
    $(wildcard include/config/securityfs.h) \
    $(wildcard include/config/security/yama.h) \
    $(wildcard include/config/mtk/root/trace.h) \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/netlink.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/netdevice.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/if_packet.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/if_link.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/if_link.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/hash.h \
  arch/arm64/include/generated/asm/hash.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/hash.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/neighbour.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/rtnetlink.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/rtnetlink.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/rtnetlink.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/if_addr.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/net/netlink.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/ip.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/uapi/linux/ip.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/etherdevice.h \
    $(wildcard include/config/have/efficient/unaligned/access.h) \
  arch/arm64/include/generated/asm/unaligned.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/asm-generic/unaligned.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/unaligned/access_ok.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/unaligned/generic.h \
  /home/book/work/XY3701_N0/kernel-3.18/include/linux/gsmmux.h \

/home/book/work/XY3701_N0/external/test/pcm_module/n_gsm.o: $(deps_/home/book/work/XY3701_N0/external/test/pcm_module/n_gsm.o)

$(deps_/home/book/work/XY3701_N0/external/test/pcm_module/n_gsm.o):
