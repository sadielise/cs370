/*
 * CS370: Programming Assignment 3
 * Author: Sadie Henry
 * Date: 11/9/2015
 * 
 * This is the Bounded Buffer class that contains an array of fixed
 * size and is a FIFO structure.
 */

public class BoundedBuffer {
	
	// class variables
	private final int MaxBufferSize;
	private int CurrentBufferSize;
	private double[] buffer;
	private int start, end;
	
	// constructor
	public BoundedBuffer(int size){
		MaxBufferSize = size;
		CurrentBufferSize = 0;
		buffer = new double[size];
		start = 0;
		end = -1;
	}
	
	// add item to buffer, returns index of added item
	public synchronized int add(double item){
		end = (end + 1) % MaxBufferSize;
		buffer[end] = item;
		CurrentBufferSize++;
		return end;
	}
	
	// remove item from buffer, returns index of removed item
	public synchronized int remove(){
		int ReturnValue = start;
		start = (start + 1) % MaxBufferSize;
		CurrentBufferSize--;
		return ReturnValue;
	}
	
	// returns true if buffer is empty
	public boolean empty(){
		return CurrentBufferSize == 0;
	}
	
	// returns true if buffer is full
	public boolean full(){
		return CurrentBufferSize == MaxBufferSize;
	}

}
