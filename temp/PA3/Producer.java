/*
 * CS370: Programming Assignment 3
 * Author: Sadie Henry
 * Date: 11/9/2015
 * 
 * This is the Producer class that adds items to the BoundedBuffer 
 * in a synchronized manner. Handles both parallel and non-parallel threads.
 */

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Random;

public class Producer implements Runnable {

	// class variables
	private BoundedBuffer buffer;
	private final int BufferSize;
	private int NumProduce;
	private int NumAdded;
	private int MaxWaitTime;
	private boolean parallel;

	// constructor
	public Producer(BoundedBuffer buffer, int BufferSize, int NumProduce, int MaxWaitTime, boolean parallel){
		this.buffer = buffer;
		this.BufferSize = BufferSize;
		this.NumProduce = NumProduce;
		this.NumAdded = 0;
		this.MaxWaitTime = MaxWaitTime;
		this.parallel = parallel;
	}

	// run method which provides synchronized access to the buffer
	@Override
	public void run() {

		DateFormat sfd = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.");
		Random random = new Random();

		while(NumAdded < NumProduce){
			
			// synchronized access to the buffer
			synchronized(buffer){
				
				Double BufferElement = random.nextDouble() * 100.0;

				// handle parallel case
				if(parallel){
					while(buffer.full()){
						Calendar cal1 = Calendar.getInstance();
						System.out.println("Unable to place, buffer full, at Time: " + sfd.format(cal1.getTime()) + String.format("%05d",(System.nanoTime()/100000)%100000));
						try {
							buffer.wait();
						} catch (InterruptedException e) {
							System.out.println(e);
						}			
					}

					int index = buffer.add(BufferElement);
					Calendar cal2 = Calendar.getInstance();
					System.out.println("Placed at the location: " + index + " at Time: " + sfd.format(cal2.getTime()) + String.format("%05d",(System.nanoTime()/100000)%100000));
					buffer.notify();	
				}

				// handle non-parallel case
				else{
					if(buffer.full()){
						Calendar cal1 = Calendar.getInstance();
						System.out.println("Unable to place, buffer full, at Time: " + sfd.format(cal1.getTime()) + String.format("%05d",(System.nanoTime()/100000)%100000));
						NumAdded = NumProduce;
					}
					else{
						int index = buffer.add(BufferElement);
						Calendar cal2 = Calendar.getInstance();
						System.out.println("Placed at the location: " + index + " at Time: " + sfd.format(cal2.getTime()) + String.format("%05d",(System.nanoTime()/100000)%100000));
					}
				}
			}
			
			// increment the number added and start delay
			NumAdded++;
			int TimeDelay = random.nextInt(MaxWaitTime);
			try {
				Thread.sleep(TimeDelay);
			} catch (InterruptedException e) {
				System.out.println(e);
			}
		}
	}
}
