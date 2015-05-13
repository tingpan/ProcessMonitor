#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/file.h>

#define NUMBER_OF_PROCESSES 4
#define MAX_EXPERIMENT_DURATION 1000
long int getDifferenceInMilliSeconds(struct timeval start, struct timeval end);

int main(int argc, char* argv[]){
	pid_t child_pid[NUMBER_OF_PROCESSES];
	int i, status;
	struct timeval start_time, current_time;
	const char *csv_path = "./output.csv";
	const char *html_path = "./output.html";

	//Delet csv file if it already exists
	if (access(csv_path, 0) == 0){
		remove(csv_path);
	}

	//Write HTML head
	FILE *html_file = fopen(html_path, "w");
	if (html_file != NULL){
		fprintf(html_file, "<!DOCTYPE html>\n<html>\n<head>\n<title>SVG HTML</title>\n</head>\n<body style = \"width:%dpx\">\n\n", MAX_EXPERIMENT_DURATION * 6 + 20);
	}
	else {
		printf("Can not open the html file.");
	}
	fclose(html_file);

	//CPU Affinity
	srand(time(NULL));
	cpu_set_t cpuset;
	int cpu_amount = sysconf(_SC_NPROCESSORS_CONF); //Get CPU Number
	int target_cpu = random() % cpu_amount; //Generate a random target cpu;
	CPU_ZERO(&cpuset);
	CPU_SET(target_cpu, &cpuset);
	sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpuset);

	//Set Base Time
	gettimeofday(&start_time, NULL);

	//Create Processes
	for (i = 0; i < NUMBER_OF_PROCESSES; i++){
		child_pid[i] = fork();

		if (child_pid[i] < 0){
			printf("create process error!\n");
			return;
		}
		else if (child_pid[i] == 0){
			//Set the priority of the process
			pid_t pid = getpid();
			setpriority(PRIO_PROCESS, pid, i * 5);
			int log_data[MAX_EXPERIMENT_DURATION] = { 0 };
			int time_difference;
			gettimeofday(&current_time, NULL);
			time_difference = getDifferenceInMilliSeconds(start_time, current_time);

			//Record the process id in to the array if it is running in the current time.
			while (time_difference < MAX_EXPERIMENT_DURATION){
				log_data[time_difference] = pid;
				gettimeofday(&current_time, NULL);
				time_difference = getDifferenceInMilliSeconds(start_time, current_time);
			}

			//Output the csv file
			FILE *output_csv = fopen(csv_path, "a+");
			if (output_csv != NULL){
				if (flock(output_csv->_fileno, LOCK_EX) == 0) {
					for (i = 0; i < MAX_EXPERIMENT_DURATION; i++){
						if (log_data[i] != 0)
							fprintf(output_csv, "%d, %d\n", i, log_data[i]);
					}
				}
				else {
					printf("Can not require file lock.");
				}
				fclose(output_csv);
				flock(output_csv->_fileno, LOCK_UN);
			}
			else {
				printf("Can not open the csv file.");
			}

			//Output the html file
			html_file = fopen(html_path, "a+");
			if (html_file != NULL){
				//Get a random color for each process
				srand(pid);
				int r = random() % 200;
				int g = random() % 200;
				int b = random() % 200;
				if (flock(html_file->_fileno, LOCK_EX) == 0) {
					fprintf(html_file, "<div> <p> Process Index: %d, Priority: %d, CPU ID: %d</p>\n", pid, getpriority(PRIO_PROCESS, pid), sched_getcpu());
					for (i = 0; i < MAX_EXPERIMENT_DURATION; i++){
						if (log_data[i] != 0) {
							fprintf(html_file, "<svg width=\"6px\" height=\"16px\">\n  <rect width=\"6px\" height = \"16px\" style=\"fill:rgb(%d,%d,%d);stroke-width:1px;stroke:rgb(0,0,0);\">\n  Sorry, your browser does not support inline SVG.\n</svg>", r,g,b);
						}
						else {
							fprintf(html_file, "<svg width=\"6px\" height=\"16px\">\n  <rect width=\"6px\" height = \"16px\" style=\"fill:rgb(255,255,255);stroke-width:1px;stroke:rgb(0,0,0);\">\n  Sorry, your browser does not support inline SVG.\n</svg>");
						}
					}
					fprintf(html_file, "</div>\n");
				}
				else {
					printf("Can not require file lock.");
				}
				fclose(html_file);
				flock(html_file->_fileno, LOCK_UN);
			}
			else {
				printf("Can not open the html file.");
			}
			return 0;
		}
	}

	//Execute the ps command
	pid_t pid = fork();
	if (pid < 0){
		printf("Create Process Error.");
	}
	else if (pid == 0) {
		execl("/bin/ps", "ps", "l", 0);
		return 0;
	}

	//Wait for all child processes
	for (i = 0; i < NUMBER_OF_PROCESSES; i++){
		waitpid(child_pid[i], &status, WUNTRACED);
	}

	//Write the end part of the html file
	html_file = fopen(html_path, "a+");
	if (html_file != NULL){
		fprintf(html_file, "</body></html>\n", NUMBER_OF_PROCESSES * 8);
	}
	else {
		printf("Can not open the html file.");
	}
	fclose(html_file);

	printf("This is the end of the main process\n");
	return 0;
}

long int getDifferenceInMilliSeconds(struct timeval start, struct timeval end)
{
	int seconds = end.tv_sec - start.tv_sec;
	int useconds = end.tv_usec - start.tv_usec;
	int mtime = (seconds * 1000 + useconds / 1000.0);
	return mtime;
}
