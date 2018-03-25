using namespace std;



vector<string> database1::listNewsGroup();

	void database1::createNewsGroup(string newsGroupName){
		for(int i = 0; i < newsGroups.size(); ++i){
			if(newsGroups.at(i).second == newsGroupName){
				cout << "Duplicate groupName" << endl;
				return;
			}
		}
		newsGruops.push_back(make_pair(GroupIndex, newsGroupName));

	}
	void database1::deleteNewsGroup(string newsGroupName){

	}
	vector<string> database1::listArticles(string newsGroupName){

	}
	void database1::createArticle(string newsGroupName){

	}
	void database1::deleteArticle(string newsGroupName){

	}
	string database1::getArticle(string newsGroupName, string articleName){

	}