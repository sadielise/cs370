/*
 * CS370: Programming Assignment 3
 * Author: Sadie Henry
 * Date: 11/9/2015
 * 
 * This is the Consumer class that removes items from the BoundedBuffer
 * in a synchronized manner. Handles both parallel and non-parallel threads.
 */

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Random;

public class Consumer implements Runnable {

	// class variables
	private BoundedBuffer buffer;
	private final int BufferSize;
	private int NumConsume;
	private int NumRemoved;
	private int MaxWaitTime;
	private boolean parallel;

	// constructor
	public Consumer(BoundedBuffer buffer, int BufferSize, int NumConsume, int MaxWaitTime, boolean parallel){
		this.buffer = buffer;
		this.BufferSize = BufferSize;
		this.NumConsume = NumConsume;
		this.NumRemoved = 0;
		this.MaxWaitTime = MaxWaitTime;
		this.parallel = parallel;
	}

	// run method which provides synchronized access to the buffer
	@Override
	public void run() {

		DateFormat sfd = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.");
		Random random = new Random();

		while(NumRemoved < NumConsume){
			
			// synchronized access to the buffer
			synchronized(buffer){
				
				// handle parallel case
				if(parallel){
					while(buffer.empty()){
						Calendar cal1 = Calendar.getInstance();
						System.out.println("Unable to consume, buffer empty, at Time: " + sfd.format(cal1.getTime()) + String.format("%05d",(System.nanoTime()/100000)%100000));
						try {
							buffer.wait();
						} catch (InterruptedException e) {
							System.out.println(e);
						}			
					}

					int index = buffer.remove();
					Calendar cal2 = Calendar.getInstance();
					System.out.println("Removed from location: " + index + " at Time: " + sfd.format(cal2.getTime()) + String.format("%05d",(System.nanoTime()/100000)%100000));
					buffer.notify();

				}

				// handle non-parallel case
				else{
					if(buffer.empty()){
						Calendar cal1 = Calendar.getInstance();
						System.out.println("Unable to consume, buffer empty, at Time: " + sfd.format(cal1.getTime()) + String.format("%05d",(System.nanoTime()/100000)%100000));
						NumRemoved = NumConsume;
					}
					else{
						int index = buffer.remove();
						Calendar cal2 = Calendar.getInstance();
						System.out.println("Removed from location: " + index + " at Time: " + sfd.format(cal2.getTime()) + String.format("%05d",(System.nanoTime()/100000)%100000));
					}
				}
			}
			
			// increment number removed and start delay
			NumRemoved++;
			int TimeDelay = random.nextInt(MaxWaitTime);
			try {
				Thread.sleep(TimeDelay);
			} catch (InterruptedException e) {
				System.out.println(e);
			}
		}
	}
}
