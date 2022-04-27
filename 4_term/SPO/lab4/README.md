# Lab4 - create multiple processes. (Show races condition)
<br>
The main goal: to create several processes (children) that would change the "statics" with a non-atomic operation. The child set the timer for a while. When the alarm rings, the child catches the signal and shows the statistics.
<br>
In the main process, we should have:
	'+' - create a new child named "C_k" (where k is the process number)
	'-' - kill the last child of C_k
	'k' - safely kill all children
	's' - disable all child elements to display statistics
	'g' - allow all child elements to display statistics
	's <num>' - disable C_num for displaying statistics
	'g <num>' - allow C_num to display statistics
	'p <num>' - suspend all processes and display C_num statistics. If 'g' is not entered after 5 seconds, allow all child elements to display statistics.
	'q' - safely exit the program (and kill all processes).
<br>
In the child process we should have:
	Some data structure with statistics (two integers) that will change in an infinite loop.
	Alarm handler reimplemented to output statistics.

<br>
The child after a few cycles must send a request to the parent to display statistics.
The main should have this signal handler overridden to check if this process is allowed to output statistics.

Everything is a subtlety of your implementation