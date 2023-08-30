#include<iostream>
#include<fstream>
using namespace std;
class Helper
{
public:
	static int StringLength(const char* str)
	{
		int length = 0;
			while (str[length] != '\0') {
				length++;
			}
			return length;
		
	}
	static void StringCopy(char*& dest, char*& src)
	{
		int length = StringLength(src);
		dest = new char[length + 1];
		for (int i = 0; i < length; i++) {
			dest[i] = src[i];
		}
		dest[length] = '\0';
	}
	static char* GetStringFromBuffer(char* str)
	{
		int size = StringLength(str);
		char* newStr = new char[size];
		StringCopy(newStr, str);
		return newStr;

		//allocates required memory on heap, 
	   //copy string in this memory using StringCopy and return newly created cstring.

	}
	int CompareString(const char* cstring1, const char* cstring2) 
	{	
			int l1 = StringLength(cstring1);
			int l2 = StringLength(cstring2);
			int Len = 0;
			if (l1 < l2) {
				Len = l1;
			}
			else {
				Len = l2;
			}
			for (int i = 0; i < Len; i++) {
				if (cstring1[i] == cstring2[i]) {
					continue;
				}
				else if (cstring1[i] < cstring2[i]) {
					return -1;
				}
				else if (cstring1[i] > cstring2[i]) {
					return 1;
				}
			}
			if (l1 == l2) {
				return 0;
			}
			else if (l1 < l2) {
				return -1;
			}
			else {
				return 1;
			}

	}
};
class Post; // for add to timeline member funtion
class Object // Parent class / note to self:  both page and user can like and share a post so likedby and sharedby will have type object.
{
private: 
	char* ID; // common attribute of the parent class 
public:
	Object()
	{
		ID = NULL;
	}
	~Object()
	{
		if (ID != NULL)
			delete[] ID;
	}
	void setid( char * id)
	{
		ID = id;
	}
	char* getid()
	{
		return ID;
	}
	virtual void LikePost(Post*)
	{}
    virtual void addposttotimeline(Post*)
	{}
	virtual void Print() // can print from page or user// for fname lname and pageid and text
	{}
	virtual void viewtimeline(bool) // timeline for user and page
	{}
	virtual void viewhome()
	{}
};

class Date 
{ 
	friend ostream& operator<<(ostream& out, Date& obj);// output extraction operator overloading

private:
	int d;
	int m;
	int y;

public: 
	Date(int day =0, int month =0, int year=0)
	{
		d = day;
		m = month;
		y = year;
	}
	
	
	Date operator=(Date& rhs)
	{
		d = rhs.d;
		m = rhs.m;
		y = rhs.y;

		return *this;
	}
	static Date Currentdate;
	
	void ReadDate(istream& fin)
	{
		  fin >> d;
		  fin >> m;
		  fin >> y;
		   
	}
	
    static void SetCurrentdate(int day, int month, int year)
	{
		Currentdate.d = day;
		Currentdate.m = month;
		Currentdate.y = year;

	}
    bool iswithin24hrs()
	{
		if ((Currentdate.d - d == 0 || Currentdate.d - d == 1) && Currentdate.m - m == 0 && Currentdate.y - y == 0)
			return 1; // within 24hrs
		else
			return 0;
	}
	int getday()
	{
		return d;
	}
	int getmonth()
	{
		return m;
	}
	int getyear()
	{
		return y;
	}
	~Date()
	{

	  }
};

ostream& operator<<(ostream& out, Date& rhs) // output extraction operator overloading
{
	out << rhs.d << '/' << rhs.m << '/' << rhs.y;// dd/mm/yy
	return out;
}
Date Date::Currentdate(15,11,2017);
class Activity
{
private:
	int Type;
	char* value;
public:
	Activity()
	{
		Type = 0;
		value = NULL;
	}
	~Activity()
	{
	
		if (value != NULL)
			delete[] value;
	}
	void ReadActivity(istream& fin)
	{
		fin >> Type;
		char* temp = new char[50];
		fin.getline(temp,50);
		value = Helper::GetStringFromBuffer(temp);
	}
	void ViewActivity()
	{
		if (Type == 1)
		{
			cout << "feeling " << value<<endl;
		}
		else if (Type == 2)
		{
			cout << "thinking about " << value<<endl;
		}
		else if (Type == 3)
		{
			cout << "Making " << value<<endl;
		}
		else if (Type == 4)
		{
			cout << "celebrating " << value<<endl;
		}
		else {
			cout << "Error in activity";
		}
	}
};

class Comment
{
private: 
	char* commentid;
	Object* CommentBy;
	char* text;
	
public:
	Comment()
	{
		commentid = NULL;
		CommentBy = NULL;
		text = NULL;
	}
	void setcommentid(char* temp)
	{
		commentid = Helper::GetStringFromBuffer(temp);
	}
	char* getcommentid()
	{
		return commentid;
		
	}
	void setcommenter(Object* Cptr)
	{
		CommentBy = Cptr;
	}
	Object* getcommenter()
	{
		return CommentBy;
	}
	void setText(char* temp)
	{
		text = Helper::GetStringFromBuffer(temp);
	}
	char* gettext()
	{
		return text;
	}

	~Comment()
	{
		
		if (commentid != NULL)
			delete[] commentid;
		if (text != NULL)
			delete[] text;
		
	}
	
};

class Post {
	int isactivity;
	char* Postid;
	const char* Text;
	Date SharedDate;
	Activity* activity;
	Object* SharedBy;
	Object** LikedBy;
	Comment** commentsonpost;
	int likedcount;
	int commentcount;
	
public: 
	Post()
	{
		isactivity = 0;
		Postid = NULL;
		Text = NULL;
		activity = NULL;
		SharedBy = NULL;
		LikedBy = new Object* [10];
		commentsonpost = new Comment*[10];
		likedcount = 0;
		commentcount = 0;
		
	}
	~Post()
	{
		if(Postid != NULL)
		delete[] Postid;
		if (Text != NULL)
		delete[] Text;
		if (LikedBy != NULL)
		{
			delete[] LikedBy;
		}
		if (commentsonpost != NULL)
		{
			for (int i = 0; i < commentcount; i++)
			{
				delete commentsonpost[i];
			}
			delete[] commentsonpost;
		}
	}
	void showshareddate() // to see when the post was shared
	{
		cout<< SharedDate; // overloaded extraction operator
	}
	void setsharedby(Object* Optr)
	{
		SharedBy = Optr;
	}
	void settext(const char* t)
	{
		Text = t;
	}
	Date getshareddate()
	{
		return SharedDate;
	}
	Object* getsharedby() // for seeing who shared a memory
	{
		return SharedBy;
	}
	void setlikedby(Object* Optr)
	{
		if (likedcount < 11)
		{
			LikedBy[likedcount] = Optr;
			likedcount++;
		}
	}
	char* getpostid()// for searchpostbyid function
	{
		return Postid;
	}
	void setdate(Date D)
	{
		SharedDate = D;//overloaded assignment
	}
	void ReadData(istream& fin)
	{
		fin >> isactivity;
		char* temp = new char[100];
		fin >> temp;
		Postid = Helper::GetStringFromBuffer(temp);
		
		SharedDate.ReadDate(fin);
		fin.ignore();
		fin.getline(temp,100);
		Text = Helper::GetStringFromBuffer(temp);
		if (isactivity == 2) // reading post with activity
		{
			this->activity = new Activity();
			activity->ReadActivity(fin);
        }
		
		// note: if exception , do this in Facebook's scope
		//fin >> temp;
		//Facebook instance;// non static members functions need to be called using an instance of the class (stack overflow)
		//SharedBy = instance.SearchUserById(temp);
		//if (SharedBy == NULL) // if not read by a user but a page
		//{
		//	SharedBy = instance.SearchPageById(temp);
		//}
	}
	void addcommenttopost(Comment* Cptr) //setter for comments
	{
		
		if (commentcount < 10) // ten commments per post
		{
			commentsonpost[commentcount] = Cptr;
			commentcount++;
			
		}
	}
	void ViewPost()
	{
		if (Postid != NULL)
			cout << "\nID: " << Postid << "\n";
		if (Text != NULL)
			cout << "Topic: " << Text << "\n";
		if (isactivity == 2) // Activity post
		{
			activity->ViewActivity();
		}
		cout << "\nShared By: \n"; SharedBy->Print(); cout<< endl<<endl;
		cout << "Liked By: \n";
		for (int i = 0; i < likedcount; i++)
		{
			LikedBy[i]->Print(); cout << "\n";
		}
		cout << "\n";
		cout << "Comments Section:\n";
		for (int i = 0; i < commentcount; i++)
		{
			
		    commentsonpost[i]->getcommenter()->Print(); 
			cout << "  Wrote:" << commentsonpost[i]->gettext();
			cout << endl;
		}
		
	}
	void viewtimeline(bool dateflag, bool commentflag ) // one print function for viewhome and viewtimeline
	{       
		cout << endl;
			if (isactivity == 2)
			{
				SharedBy->Print(); cout << " is "; activity->ViewActivity();
			}
			cout << "\"" << Text << "\" ...."; 
            if (dateflag == true) // for viewhome
				cout <<"( "<<  SharedDate<<" )\n";
			if(commentflag) // for sharedate 
				for (int i = 0; i < commentcount; i++)
				{
					cout << "\t";
					commentsonpost[i]->getcommenter()->Print();
					cout << " Wrote:" << commentsonpost[i]->gettext();
					cout << endl;
				}
	}
	void ViewLikedList()
	{
		cout << "Post Liked By: \n";
		for (int i = 0; i < likedcount; i++)
		{
			LikedBy[i]->Print(); cout << endl;
		}
	}
	bool isMemory()
	{
		if (SharedDate.getday() == Date::Currentdate.getday() && SharedDate.getmonth() == Date::Currentdate.getmonth() && SharedDate.getyear() != Date::Currentdate.getyear())
		{
			cout << Date::Currentdate.getyear() - SharedDate.getyear() << " Years Ago.\n"; return true;
		}
		return false;
	}
	int getcommentcount() // for adding comment functionality
	{
		return commentcount;
	}
	
	
};

class PAGE : public Object // polymorphic design
{
private:
	char* title;
	Post** timeline;
	int postcountpages;
public: 
	
	PAGE() //default constructor
	{
		
		title = NULL;
		timeline  = new Post * [10];
		postcountpages = 0;
	}
	
	char* getTitle()
	{
		return title;
	}
	void Print()
	{
		cout <<getid()<<" "<< title;
	}
	void ReadData(ifstream& fin)
	{
		char* temp = new char[100];
		fin >> temp;
		Object::setid(Helper::GetStringFromBuffer(temp));
		fin.ignore();
		fin.getline(temp,100);
		title = Helper::GetStringFromBuffer(temp);
		delete[] temp;
		
	}
	void addposttotimeline(Post* Pptr)
	{
		if (postcountpages < 10)
		{
			timeline[postcountpages] = Pptr;
			postcountpages++;
		}
	}
	void viewtimeline()
	{
		for (int i = 0; i < postcountpages; i++)
			timeline[i]->viewtimeline(true,true);
	}
	void viewhome()
	{ 
		for ( int i= 0; i < postcountpages; i++)
			 if (timeline[i]->getshareddate().iswithin24hrs())
			 {
				 timeline[i]->viewtimeline(false,true);
			 }
	}
	void LikePost(Post* Pptr)
	{
		Pptr->setlikedby(this);
	}
	void ViewPage()
	{
		
		for (int i = 0; i < postcountpages; i++)
		{
			timeline[i]->viewtimeline(true,true);
		}
	}

	~PAGE()
	{
		
		
		if (title != NULL)
		{
			delete[] title;
		}
		if (timeline != NULL)
		{
			
			delete[] timeline;
			timeline = NULL;
		}
	}
	
	
};

class Memory : public Post 
{
private:
	Post* originalPost;
	
public:
	Memory(Object* sharedby, Post* Pptr, const char* t)
	{
		originalPost = Pptr;
		
		setsharedby(sharedby);
		setdate(Date::Currentdate);
		settext(t);
	}
	~Memory()
	{
		
	}
	

	

	
};

class user : public Object // polymorphic design 
{
private:
	//char* userid;
	char* fname;
	char* lname;
	PAGE** likedpages;
	user** friendlist;
	int pagecount, friendcount;
	Post** timeline;
	int postcountuser;
public: 
	user()//default constructor
	{
		//userid = NULL;
		fname = NULL;
		lname = NULL;
		pagecount = friendcount = 0;
		likedpages = new PAGE * [10];
		friendlist = new user * [10];
		timeline = new Post * [10];
		postcountuser = 0;
	}
	char* getfname()
	{
		return fname;
	}
	char* getlname()
	{
		return lname;
	}
	void Print()
	{
		cout << fname << " " << lname;
	}
	void ReadData(ifstream& fin)
	{
		char * temp  = new char[50];
		fin >> temp;
		Object::setid(Helper::GetStringFromBuffer(temp));
		fin >> temp;
		fname = Helper::GetStringFromBuffer(temp);
		fin >> temp;
		lname = Helper::GetStringFromBuffer(temp);
		delete[] temp;
	}
	void addposttotimeline(Post* Pptr)
	{
		if (postcountuser < 10)
		{
			timeline[postcountuser] = Pptr;
			postcountuser++;
		}
	}
	~user() // Deallocation
	{
		
		if (fname != NULL)
		{
			delete[] fname;
		}
		if (lname != NULL)
		{
			delete[] lname;
		}
		if (likedpages != NULL)
		{
			delete[] likedpages;
		}
		if (friendlist != NULL)
		{
			delete[] friendlist;
		}
		if (timeline != NULL)
		{
			
		  delete[] timeline;
		  timeline = NULL;
		}
	}
	void LikePost(Post* Pptr)
	{
		Pptr->setlikedby(this);
	}
	
	void pagelike(PAGE* pageptr)
	{
		if (pagecount <= 10)
		{
			likedpages[pagecount] = pageptr;
			pagecount++;
		}
		else
		{
			cout << "Cannot like anymore pages";
		}
	}
	void AddFriend(user* userptr)
	{
		if (userptr != NULL)
		{
			friendlist[friendcount] = userptr;
			friendcount++;
		}
		else {
			friendlist[friendcount] = NULL;
			friendcount++; ;
		}
	}
	
	void PrintFriendsList() {
		
		if (friendcount != 0) {
			cout << "Friends List of " << fname << " " << lname << endl;
			for (int i = 0; i < friendcount; i++) {
				cout << i + 1 << ". " << friendlist[i]->fname << " " << friendlist[i]->lname << "\n";
			}
		}
		else
			cout << "User has no friends added.\n";
	}

	void PrintLikedPages() {
		if (pagecount != 0) {
			cout << fname << " " << lname << " likes the following pages:" << endl;
			for (int i = 0; i < pagecount; i++) {
				cout << i + 1 << ". " << likedpages[i]->getid() << " - " << likedpages[i]->getTitle() << "\n";
			}
		}
		else
			cout << "User did not like any pages.\n";
	}
	void viewtimeline()
	{
		for (int i = 0; i < postcountuser; i++) 
		{
			timeline[i]->viewtimeline(true,true);
		}
	}

	void viewhome()
	{
		for (int i = 0; i < postcountuser; i++)
				if (timeline[i]->getshareddate().iswithin24hrs())
				{
					timeline[i]->viewtimeline(false,true);
				}
		
	}

	void ViewHome()
	{
		
		for (int i = 0; i < friendcount; i++)
		{
			friendlist[i]->viewhome();
		}
		for (int i = 0; i < pagecount; i++)
		{
			likedpages[i]->viewhome();
		}
	}
	void SeeYourMemories()
	{
		cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n"; \
			cout << "On this day" << endl;
		for (int i = 0; i < postcountuser; i++)
		{
			if (timeline[i]->isMemory())
				timeline[i]->viewtimeline(true,true);
		}
	}
	void ShareMemory(Post* Pptr, char* t)
	{

		Memory* Mptr = new Memory(this, Pptr, t); // this can be a user or a page (Object*)
		cout << "\n\n"; Pptr->getsharedby()->Print(); cout << " Shared a Memory \n" << " on "; 
	    Pptr->showshareddate();
		Mptr->viewtimeline(true,false); // text attribute changed to const char
		cout <<"\n";
		Pptr->viewtimeline(true,true);// rest of the timeline
		
		
	}

	void PostComment(Post* Pid, char* comment)
	{
		Comment* newcomment = new Comment();
		newcomment->setText(comment);
		newcomment->setcommenter(this); // this = will be current user pointer
		
		//newcomment->setcommentid(newcomment->newcommentid()); // eg c1, c2 etc.
		Pid->addcommenttopost(newcomment);
		
	}
	
};



class Facebook //Controller Class
{
private:
	 PAGE** pagelist;  int totalpages;
	 user** userlist;  int totalusers;
	 Post** posts;  int totalposts;
	 
	 int totalcomments;
	
public:
	
	void FriendsListUpdate(ifstream & fin , char** friendid)
	{
		char* temp = new char[5];
		int i = 0;
		fin >> temp;
		while (temp[0] != '-')
		{
			friendid[i] = Helper::GetStringFromBuffer(temp);
			fin >> temp;
			i++;

		}
		
		if (temp[0] == '-')
		{
			friendid[i] = NULL;
		}
		
	}

	 PAGE* SearchPageById(char* pageid)
	 {
		for (int i = 0; i < totalpages; i++)
		{
			char* temp = pagelist[i]->getid();
			//int flag = Helper::CompareString(temp, pageid);
			Helper Comp;
			int flag = Comp.CompareString(temp,pageid);
			if (flag == 0 )
			{
				return pagelist[i];
			}
		}
		return NULL; // no page found
		
	 }

	 user* SearchUserById(char* friendid)
	{
		if (friendid != NULL)
		{
			for (int i = 0; i < totalusers; i++)
			{
				char* temp = userlist[i]->getid();
				Helper Comp;
				int flag = Comp.CompareString(temp, friendid);
			    if (flag == 0)
				{
					return userlist[i];
				}
				
			}
		}
		else
		{
			return NULL;// if no user is found
		}
		
	}

	 Object* SearchObjectById(char* UorP)
	 {
		 
		 if (UorP[0] == 'u')
		 {
		     user* SharedBy = SearchUserById(UorP);
			 return SharedBy;
		 }
		 else if (UorP[0] == 'p')
		 {
			 PAGE* SharedBy = SearchPageById(UorP);
			 return SharedBy;
		 }
		 else {
			 return NULL; // no object found (user or page)
		 }
	 }

	 Post* SearchPostById(char* Postid)
	 {
		 if (Postid != NULL)
		 {
			 for (int i = 0; i < totalposts; i++)
			 {
				 char* temp = posts[i]->getpostid();
				 Helper Comp;
				 int flag = Comp.CompareString(temp, Postid);
				 if (flag == 0)
				 {
					 return posts[i];
				 }
			 }
		 }
		 return NULL; //no post found
	 }

	void LoadPages()
	{
		ifstream fin;

		fin.open("Pages.txt");
		if (fin.is_open())
		{
			fin >> totalpages;
			pagelist = new PAGE * [totalpages];
			for (int i = 0; i < totalpages; i++)
			{
				pagelist[i] = new PAGE();
				pagelist[i]->ReadData(fin);
				
			}



			fin.close();
		}
		else
		{
			cout << "File not open";
		}

	}

	void LoadUsers()
	{
		ifstream fin;
		fin.open("Users.txt");
		if (fin.is_open())
		{
			fin >> totalusers;
			userlist = new user * [totalusers];
			PAGE* pageptr;
			user* userptr;
			char*** friendid = new char** [totalusers];
			for (int i = 0; i < totalusers; i++)
			{
				friendid[i] = new char* [10];
				
				userlist[i] = new user();
				userlist[i]->ReadData(fin);
				FriendsListUpdate(fin, friendid[i]);
				char* temp = new char [5];
				fin >> temp;
				while (temp[0] != '-')
				{
					pageptr = SearchPageById(temp);
					userlist[i]->pagelike(pageptr);
					fin >> temp;
				}
			}
			int i = 0;
			if (friendid[i] != NULL)
			{
				for (; i < totalusers; i++)
				{
					for (int j = 0; friendid[i][j] != NULL; j++)
					{
						userptr = SearchUserById(friendid[i][j]);
						userlist[i]->AddFriend(userptr);
					}
				}
			}
			fin.close();
			
		}
	}

	void LoadPosts()
    {
		ifstream fin;
		fin.open("Posts.txt");
		if (fin.is_open())
		{
			fin >> totalposts;
			 posts = new Post * [12];
			for (int i = 0; i < totalposts; i++)
			{
				posts[i] = new Post();
				posts[i]->ReadData(fin);

				char* UorP = new char[10];
			    fin >> UorP;
				Object* uorpPtr = SearchObjectById(UorP);
				posts[i]->setsharedby(uorpPtr);
				uorpPtr->addposttotimeline(posts[i]);
				fin >> UorP;
			    while (UorP[0] != '-')
				{ 
					Object* LikedBy = SearchObjectById(UorP);
					posts[i]->setlikedby(LikedBy);
					fin >> UorP;
				}
				
			}
			
		}
	}

	void LoadComments()
	{
		ifstream fin;
		fin.open("Comments.txt");
		if (fin.is_open())
		{
			fin >> totalcomments;
			//comments = new Comment * [10];
			char* temp = new char[100];
			char* PostId;
			for (int i = 0; i < totalcomments; i++)
			{
				Comment* comments = new Comment();
				fin >> temp;
				comments->setcommentid(temp);
				fin >> temp;
				PostId = Helper::GetStringFromBuffer(temp);
				Post * Pptr = SearchPostById(PostId);
				fin >> temp;
				Object* commenterptr = SearchObjectById(temp); // comment by
				comments->setcommenter(commenterptr);
				fin.getline(temp, 100);
				comments->setText(temp);
				Pptr->addcommenttopost(comments);
				
			}
		}
	}

	void Load()
	{
		LoadPages(); LoadUsers(); LoadPosts(); LoadComments();
	}
	void Run()
	{
		cout << "Set Cuurent System Date: ( 15, 11, 2017 ) \n\n";

		char U[] = "u7";
		user* currentuser = SearchUserById(U);
		cout << "Cuurent User Set To: "; currentuser->Print();cout<< "\n\n";
		cout << "Command ViewFriendsList\n-------------------------------------------------\n";
		currentuser->PrintFriendsList();
		cout << "Command View Liked Pages\n-------------------------------------------------\n";
		currentuser->PrintLikedPages();

		char P[] = "post5";
		Post* currentpost = SearchPostById(P);
		/*cout << "-------------------------------------------------\nCommand ViewPost:\n";
		currentpost->ViewPost();*/
		cout << endl;
		cout << "-------------------------------------------------\nCommand ViewHome:\n";
		currentuser->ViewHome();
		cout << endl;
		cout << "-------------------------------------------------\nCommand Timeline:\n";
		currentuser->viewtimeline();
		cout << endl;
		cout << "-------------------------------------------------\nCommand View Liked List\n";
		currentpost->ViewLikedList();
		cout << "--------------------------------------------------\n";
		cout << "Command Like Post (" << currentpost->getpostid() << ") \n";
		currentuser->LikePost(currentpost);
		cout << "--------------------------------------------------\nCommand View Liked List\n";
		currentpost->ViewLikedList();

		char Posttocomment1[] = "post4";
		currentpost = SearchPostById(Posttocomment1);
		char commenttext1[] = "Good Luck for your Result .";
		cout << "\n----------------------------------------------------\nCommand Post Comment ( " << Posttocomment1 << " \"" << commenttext1 << "\" )";
		currentuser->PostComment(currentpost, commenttext1);
		cout << "\n";
		currentpost->viewtimeline(true,true);

		char Posttocomment2[] = "post8";
		currentpost = SearchPostById(Posttocomment2);
		char commenttext2[] = "Thanks for the wishes.";
		cout << "\n----------------------------------------------------\nCommand Post Comment ( " << Posttocomment2 << " \"" << commenttext2 << "\" )";
		currentuser->PostComment(currentpost, commenttext2);
		cout << "\n";
		currentpost->viewtimeline(true,true);

		
		

		cout << "--------------------------------------------------\nCommand SeeYourMemories\n";
		currentuser->SeeYourMemories();

		char MemoryPost[] = "post10";
		currentpost = SearchPostById(MemoryPost);
		char MemoryText[] = "Never thought I will be specialist in this field...";

		cout << "----------------------------------------------------\nCommand Share Memory ( "<< MemoryPost<<" \""<<MemoryText<<"\" )";
		currentuser->ShareMemory(currentpost, MemoryText);
		cout << "\nCommand View Timeline\n";
		currentuser->viewtimeline();

		cout << "----------------------------------------------------\nCommand View Page\n";
		char pagename[] = "p1";
		PAGE* currentpage = SearchPageById(pagename);
		currentpage->ViewPage();
	}
	~Facebook()

	{
		

		if (pagelist != NULL)
		{
			for( int i = 0 ; i < totalpages;i++)
				if(pagelist)
					delete pagelist[i];
			delete[] pagelist;
			
		}
		if (userlist != NULL)
		{
			for (int i = 0; i < totalusers; i++)
				if(userlist[i])
					delete userlist[i];
			delete[] userlist;

		}
		if (posts != NULL)
		{
			for (int i = 0; i < totalposts; i++) 
			{
				if(posts[i])
					delete posts[i];
			}
			delete[] posts;
		}

		
	}
	
};

void main()
{   

	Facebook fb;
	fb.Load();
	fb.Run();
}
