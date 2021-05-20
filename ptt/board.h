#pragma once
#include "user.h"
#include <vector>
enum vote
{
	UPVOTE,
	DOWNVOTE
};
struct Comment
{
	bool vote;
	string message;
};
struct Post
{
public:
	void setTitle();
	void setContent();
	void setComment();
	string title;
	string content;
	vector<Comment> comments;
};
class Board
{
	void editBoard();
	Board();
private:
	vector<Post> posts;
};