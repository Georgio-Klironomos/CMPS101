//-----------------------------------------------------------------------------
// Georgio Klironomos
// gklirono
// Programming Assignment 1
// List ADT for CMPS 101
//-----------------------------------------------------------------------------
//WORKS CITED
//http://javadevnotes.com/java-string-array-examples
//https://alvinalexander.com/java/java-string-array-reference-java-5-for-loop-syntax
//https://www.geeksforgeeks.org/doubly-linked-list/
//https://classes.soe.ucsc.edu/cmps101/Fall18/Examples/Java/Queue/Queue.java

class List{

    private class Node{
      // Fields
      int data;
      Node next;
      Node prev;
      
      // Constructor
      Node(int data) { this.data = data; next = null; prev = null;}
      
      // toString():  overrides Object's toString() method
      public String toString() {
         return String.valueOf(data);
      }
      
   }
   
   //Fields
   private Node front;
   private Node back;
   private Node cursor;
   private int length;
   private int index;

    //constructor
    List() {
        front = back = cursor = null;
        length = 0;
        index = -1;
    }    
    //access functions
    int length() {
        return length;
    }
    int index() {
        return index;
    }

    int front() {
        if(length > 0) {
            return front.data; 
		}
		else {return -1;}
    }
    int back() {
        if(length > 0) {
            return back.data; 
		}
		else {return -1;}
    }
    int get() {
		if(index >= 0) {
                return cursor.data; 
		}
		else {return -1;}
    }
    boolean equals(List L) {
        //true if and only this List and passed-in L are the same integer sequence.
        //while loop using both cursor and comparing each element, maybe
        if(L.length != length){
            return false;
        }
        else{
            List.Node current1 = front;
            List.Node current2 = L.front;
            while (current1 != null){
                if(current1.data != current2.data){
                    return false;
                }    
                current1 = current1.next;
                current2 = current2.next;    
            }    
            return true;
        }
    }
    //manipulation procedures
    void clear() {
        while(length > 0){
            deleteFront();
        }
    }
    void moveFront() {
        if(length > 0) {
            cursor = front;
            index = 0;
        }
    }
    void moveBack() {
        if(length > 0) {
            cursor = back;
            index = (length-1);
        }
    }
    void movePrev() {
        if(cursor != null){
            cursor = cursor.prev;
            index--;
        }
    }
    void moveNext()  {
        if(cursor != null){
            cursor = cursor.next;
            if(index == (length-1)) {index = -1;}
            else{index++;}
        }
    }
    void prepend(int data) {
        List.Node new_node = new List.Node(data);
		if(length()>0){
			new_node.next = front;
			front.prev = new_node;
			front = new_node;
		}
		if(length() == 0){
	    	front = new_node;
	    	back = new_node;
		}
        length++;
        if(cursor != null){
            index++;//NEW!
        }
    }
    void append(int data) {
        List.Node new_node = new List.Node(data);		
        if(length() > 0){	
            back.next = new_node;				
            new_node.prev = back;				
            back = new_node;				
        }   
        if(length() == 0){
            front = new_node;
            back = new_node;
        }
        length++;
    }
    void insertBefore(int data) {
        if(length > 0 && index >= 0) {
            List.Node new_node = new List.Node(data);
            new_node.next = cursor;
            if(cursor.prev != null) {
                new_node.prev = cursor.prev;
                cursor.prev.next = new_node;
            }
            cursor.prev = new_node;
            if(cursor == front){
                front = new_node;
            }
            length++;
            index++;
        }
    }    
    void insertAfter(int data) {
        if(length > 0 && index >= 0) {
            List.Node new_node = new List.Node(data);
            new_node.prev = cursor;
            if(cursor.next != null) {
                new_node.next = cursor.next;
                cursor.next.prev = new_node;
            }
            cursor.next = new_node;
            if(cursor == back){
                back = new_node;
            }
            length++;
        }
    }
    void deleteFront() {
        if (length <= 0 || front == null){
            return;
        }
        if (front.next!=null){
            List.Node frontNext = front.next;
            frontNext.prev = null;
        }
        if(cursor == front){
            cursor = null;
            index = -1;
        }
        front = front.next;
        length--;
    }
    void deleteBack() {
        if (length <= 0 || back == null){
            return;
        }
        if (back.prev!=null){
            List.Node backPrev = back.prev;
            backPrev.next = null;
        }
        if(cursor == back){
            cursor = null;
            index = -1;
        }
        back = back.prev;
        length--;
    }    
    void delete() {
        if (length <= 0 || length <0 || cursor == null){
            return;
        }
        if(cursor.prev!=null){
            List.Node cursorPrev = cursor.prev;
            cursorPrev.next = cursor.next;
            if(back == cursor){
                back = cursorPrev;
            }
        }
        if(cursor.next!=null){
            List.Node cursorNext = cursor.next;
            cursorNext.prev = cursor.prev;
             if(front == cursor){
                front = cursorNext;
            }
        }
        cursor = null;
        index = -1;
        length--;
    }
    //other methods
    public String toString(){
        String listString = "";
        List.Node current = front;
        while(current != null){
            listString += Integer.toString(current.data) +" ";
            current = current.next;
        }
        String cursorStr = "null";
        if (cursor != null) {
            cursorStr = Integer.toString(cursor.data);
        }
        return listString;
    }
    List copy() {
        List newList = new List();
        List.Node current = front;
        while(current != null) {
            newList.append(current.data);
            current = current.next;
        }
        return newList;
    }
    List concat(List L) {
        List newList = new List();
        List.Node current = front;
        while(current != null) {
            newList.append(current.data);
            current = current.next;
        }
        current = L.front;
        while(current != null) {
            newList.append(current.data);
            current = current.next;
        }
        return newList;
    }
}
