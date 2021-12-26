#ifdef TYPE
#ifdef TYPEN

#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a ## b

	class CONCAT(llist_,TYPEN)
	{
	public:
		CONCAT(llist_,TYPEN)();
		~CONCAT(llist_,TYPEN)();

		struct listNode
		{
			TYPE value;
			listNode* next;
		};

		void insertFront(TYPE t);
		TYPE top();
		void pop();
		TYPE getPredicate(int (*fun)(TYPE,void*),void*);
		void removePredicate(int (*fun)(TYPE,void*),void*);
		int len();
		listNode* head;

		static listNode* newListNode(TYPE t);

	private:

	};

#endif
#endif
