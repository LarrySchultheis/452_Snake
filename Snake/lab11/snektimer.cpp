#include "snektimer.h"
#include	<unistd.h>
#include	<signal.h>
#include	<sys/time.h>

#define TIMERCNT 8

void timerhandler();
int	 timercnt;
struct	 timeval alarmtimes[TIMERCNT];



SnekTimer::SnekTimer()
{
    timerMain();
}


void SnekTimer::timerMain()
{
    struct itimerval times;
    sigset_t	sigset;
    int		i, ret;
    struct sigaction act;
    siginfo_t	si;

    /* block SIGALRM */
    sigemptyset (&sigset);
    sigaddset (&sigset, SIGALRM);
    sigprocmask (SIG_BLOCK, &sigset, NULL);

    /* set up handler for SIGALRM */
    act.sa_action = timerhandler;
    sigemptyset (&act.sa_mask);
    act.sa_flags = SA_SIGINFO;
    sigaction (SIGALRM, &act, NULL);
    /*
     * set up interval timer, starting in three seconds,
     *	then every 1/3 second
     */
    times.it_value.tv_sec = 3;
    times.it_value.tv_usec = 0;
    times.it_interval.tv_sec = 0;
    times.it_interval.tv_usec = 333333;
    ret = setitimer (ITIMER_REAL, &times, NULL);
    printf ("main:setitimer ret = %d\n", ret);

    /* now wait for the alarms */
    sigemptyset (&sigset);
    timerhandler (0, si, NULL);
    while (timercnt < TIMERCNT) {
        ret = sigsuspend (&sigset);
    }
    printtimes();
}

void SnekTimer::timerHandler (sig, siginfo, context)
{
    int		sig;
    siginfo_t	*siginfo;
    void		*context;
    printf ("timerhandler:start\n");
    gettimeofday (&alarmtimes[timercnt], NULL);
    timercnt++;
    printf ("timerhandler:timercnt = %d\n", timercnt);
}

void SnekTimer::printTimes ()
{
    int	i;

    for (i = 0; i < TIMERCNT; i++) {
        printf("%ld.%0l6d\n", alarmtimes[i].tv_sec,
                alarmtimes[i].tv_usec);
    }
}




