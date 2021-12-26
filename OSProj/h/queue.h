#ifdef TYPE
#ifdef TYPEN

#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a ## b

    class CONCAT(queue_,TYPEN)
	{
	public:
		CONCAT(queue_,TYPEN)();
		~CONCAT(queue_,TYPEN)();

		struct listNode
		{
			TYPE value;
			listNode* next;
			listNode* prev;
		};

		int empty();
		void insert(TYPE t);
		TYPE peek();
		TYPE remove();
		void removeNode(listNode* n);

		int size;
		listNode* head;
		listNode* tail;

		static listNode* newListNode(TYPE t);

	private:

	};

#endif
#endif


