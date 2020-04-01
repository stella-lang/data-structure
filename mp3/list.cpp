/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
   clear();
   /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
    /*ListNode* temp = tail;
    while (temp->prev != NULL){
	temp = temp->prev;
	delete temp->next;
    }
    delete head;*/
    ListNode* curr = head;
    ListNode* temp = head;
    while(curr != NULL){
    	curr = curr->next;
    	delete temp;
    	temp = curr;
    	if (curr->next == NULL){
    		delete curr;
    		curr = NULL;
    	}
    }
    length = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    /// @todo Graded in MP3.1
    ListNode* n = new ListNode(ndata);
    
    if (head != NULL){
	n->next = head;
	head->prev = n;
	head = n;
    }
    else{
	head = n;
	tail = n;
    }
    length++;
    
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
    ListNode* n = new ListNode(ndata);

    if (tail != NULL){
	tail->next = n;
	n->prev = tail;
	tail = n;
    }
    else{
	tail = n;
	head = n;
    }
    length++;
    
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    /// @todo Graded in MP3.1
    if (startPoint == endPoint||length==0 || startPoint == NULL || endPoint==NULL){
    	return;
    }
   
    ListNode* currN = startPoint;
    ListNode* nextN;
    ListNode* temp;
    ListNode* startPrev;
    ListNode* endNext;
    
    //swap startPoint and endPoint if startPoint is behind endPoint
    /*if (startPoint == tail || endPoint == head){
    	temp = startPoint;
    	startPoint = endPoint;
    	endPoint = temp;
    }*/
    
//   if ( startPoint != endPoint && startPoint != NULL && endPoint != NULL){
    	startPrev = startPoint->prev;
    	endNext = endPoint->next;
    		
    	while(currN != endPoint->next && currN!=NULL){
    		nextN = currN->next;
    		currN->next = currN->prev;
    		currN->prev = nextN;
    		currN = nextN;
    	}
    		
    		// update startpoint and endpoint
    		temp = startPoint;
    		startPoint = endPoint;
    		endPoint = temp; 
    		
    		startPoint->prev = startPrev;
    		//endNext->prev = startPoint;
    		endPoint->next = endNext;
    		//startPrev->next = endPoint;
    		
    		if(startPrev == NULL){
    			head = startPoint; //update head
    		}
    		else{
    			startPrev->next = startPoint;
    		}
    		if (endNext == NULL){
    			tail = endPoint;//update tail
    		}
    		else{
    			endNext->prev = endPoint;
    		}
    	
    	
    //}
    

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
    /// @todo Graded in MP3.1
    /*ListNode* startPoint = head;
    ListNode* endPoint = head;
    int remainLen = length;
    
    while (remainLen > n){
    	for ( int i = n-1; i > 0; i--){
    		endPoint = endPoint->next;
    	}
    	reverse(startPoint, endPoint);
    	startPoint = endPoint->next;
    	remainLen -= n;
    }
    reverse(startPoint, tail);*/
    
    if (length == 0 || n == 0 ){
    	return;
    }
    ListNode* startP = head;
    ListNode* endP = head;
    /*if ( n == 1){
    	reverse(head, tail);
    	return;
    }*/
    while(startP != NULL){
    for(int i = 1; i<n && endP->next != NULL; i++){
    	endP = endP->next;
    }
    reverse(startP, endP);
    startP = endP->next;
    endP = startP;
    }
    
    
    /*while(startP != NULL && startP->next != NULL){
    	endP = endP->next;
    }
    reverse(startP, endP);*/
    
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
    if (length == 0 || head == NULL){
    	return;
    }
    
    ListNode* curr = head;
    ListNode *next1, *next2;
    
    while(curr->next != NULL && curr->next->next != NULL){
    	next1 = curr->next;
    	next2 = curr->next->next;
    	curr->next = next2;
    	next2->prev = curr;
    	next1->prev = tail;
    	next1->next = NULL;
    	tail->next = next1;
    	tail = next1;
    	
    	curr = next2;
    }
    		
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    ListNode* curr = start;
    ListNode* temp;
    for (int i = 0; i < splitPoint; i++){
    	if(curr!= NULL){
    	curr = curr->next;
    	}
    	else{
    	return NULL;
    	}
    }
    temp = curr->prev;
    temp->next = NULL;
    curr->prev = NULL;
    
    return curr; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    /// @todo Graded in MP3.2
    ListNode* temp = NULL;
    ListNode *temp1, *temp2;
    if (first == NULL){
    	return second;
    }
    if (second == NULL){
    	return first;
    }
    if(first->data < second->data){
    	temp = first;
    	temp->next = merge(first->next, second);
    }
    else{
    	temp = second;
    	temp->next = merge(first, second->next);
    }
    temp1 = temp;
    temp2 = temp->next;
    while(temp2 != NULL){
    	temp2->prev = temp1;
    	temp1 = temp2;
    	temp2 = temp2->next;
    }
    
    return temp;
    
    // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    if (chainLength <= 1){
    	return start;
    }
    ListNode* newlist = split(start, chainLength/2);
    start = mergesort(start, chainLength/2);
    newlist = mergesort(newlist, chainLength - chainLength/2);
    return merge(start, newlist); // change me!
}
