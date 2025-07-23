/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egache <egache@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:13:53 by egache            #+#    #+#             */
/*   Updated: 2025/07/23 23:27:16 by egache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// void *thread(void *arg) {
//   char *ret;
//   printf("thread() entered with argument '%s'\n", arg);
//   if ((ret = (char*) malloc(20)) == NULL) {
//     perror("malloc() error");
//     exit(2);
//   }
//   strcpy(ret, "This is a test");
//   pthread_exit(ret);
// }

// main() {
//   pthread_t thid;
//   void *ret;

//   if (pthread_create(&thid, NULL, thread, "thread 1") != 0) {
//     perror("pthread_create() error");
//     exit(1);
//   }

//   if (pthread_join(thid, &ret) != 0) {
//     perror("pthread_create() error");
//     exit(3);
//   }

//   printf("thread exited with '%s'\n", ret);
// }

int	main(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec;
	printf("timeoftheday : %ld", time);
	while (1)
	{
		gettimeofday(&tv, NULL);
		printf("tv.tv_sec : %ld\n", tv.tv_sec);
		printf("time : %ld\n", time);
		usleep(10000);
	}
	return (0);
}
