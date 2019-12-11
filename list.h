/* List Node Class, */

class ListNode{
public:
	/* save vertex, and flight time */
	int vertex;
	int time;
	/* next pointer */
	ListNode* next;
	ListNode(int v, int t){
		vertex = v;
		time = t;
		next = NULL;
	}
};


class List{
public:
	int size;
	ListNode *head, *tail;
	List(){ // Constructor
		size = 0;
		head = NULL;
		tail = NULL;
	}
	
	~List(){ // Destructor
		ListNode *temp = head;
		ListNode *prev;
		while(temp != NULL){
			prev = temp;
			temp = temp->next;
			delete(prev);
		}
	}

	/* find the Node[vertex == id] in the list 
	*  not found - return -1, found - return time
	*/
	int find(int id){
		ListNode *temp = head;
		int cnt = -1;
		while(temp != NULL){
			if(temp->vertex == id){
				cnt = temp->time;
				break;
			}
			temp = temp->next;
		}
		return cnt;
	}
	
	/* push fail - return 0, success - return 1 */
	int push(int id, int time){
		/* there is already id Node */
		int check = find(id);
		if(check != -1){
			return 0;
		}
		/* make a new node */
		ListNode *temp = new ListNode(id,time);
		if(head == NULL){ // no head
			head = temp;
			tail = temp;
		}else{
			tail->next = temp;
			tail = temp;
		}
		return 1;
	}
	
};
