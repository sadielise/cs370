/*
 * CS370: Programming Assignment 3
 * Author: Sadie Henry
 * Date: 11/9/2015
 * 
 * This is the main class that creates the buffer, 2 consumers, and 3 producers.
 */

public class Main {
	
	public static void main(String[] args){
		
		// initialize variables
		int BufferSize = 0; // stays fixed
		int NumItems = 0; // can be less than or greater than BufferSize
		int MaxWaitTime = 0; // in milliseconds
		
		// check number of args
		if(args.length != 3){
			System.out.println("Error: Incorrect number of arguments.");
			System.exit(-1);
		}
		
		// get command line args
		try{
			BufferSize = Integer.parseInt(args[0]);
			//System.out.println("Buffer Size: " + BufferSize);
		} catch(NumberFormatException e){
			System.out.println("Error: First argument is not an integer.");
			System.exit(-1);
		}
		
		try{
			NumItems = Integer.parseInt(args[1]);
			//System.out.println("Number of Items: " + NumItems);
		} catch(NumberFormatException e){
			System.out.println("Error: Second argument is not an integer.");
			System.exit(-1);
		}
		
		try{
			MaxWaitTime = Integer.parseInt(args[2]);
			//System.out.println("Max Wait Time: " + MaxWaitTime);
		} catch(NumberFormatException e){
			System.out.println("Error: Third argument is not an integer.");
			System.exit(-1);
		}
		
		// create buffer
		BoundedBuffer buffer = new BoundedBuffer(BufferSize);
		
		// create and run producers and consumers
		Producer producer1 = new Producer(buffer, BufferSize, NumItems, MaxWaitTime, false);
		producer1.run();
		
		Consumer consumer1 = new Consumer(buffer, BufferSize, NumItems, MaxWaitTime, false);
		consumer1.run();
		
		Thread producer2 = new Thread(new Producer(buffer, BufferSize, NumItems, MaxWaitTime, true));
		Thread producer3 = new Thread(new Producer(buffer, BufferSize, NumItems, MaxWaitTime, true));
		Thread consumer2 = new Thread(new Consumer(buffer, BufferSize, (2*NumItems), MaxWaitTime, true));
		producer2.start();
		producer3.start();
		consumer2.start();
		
		try {
			producer2.join();
			producer3.join();
			consumer2.join();
		} catch (InterruptedException e) {
			System.out.println(e);
		}	
	}
}
