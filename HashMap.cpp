#include "HashMap.hpp"
#include <string>
#include <iostream>

namespace
{
	unsigned int defaultHash(const std::string& key)
	{
		unsigned int a = 54059;
		unsigned int b = 76963;
		unsigned int h = 0;

		for (int i = 0; i < key.length(); i++)
		{
			h = h * b + key[i];
			b = b * a;
		}

		return (h & 0x7FFFFFFF);
	}
}

HashMap::HashMap()
	: sz{0}, cap{INITIAL_BUCKET_COUNT}
{
	hashFunction = defaultHash;

	bucketList = new Node*[cap];
	newBucketList = nullptr;

	createFirstArray(bucketList, cap);
}

HashMap::HashMap(HashFunction hashFunc)
	: hashFunction{hashFunc}, sz{0}, cap{INITIAL_BUCKET_COUNT}
{
	bucketList = new Node*[cap];
	newBucketList = nullptr;

	createFirstArray(bucketList, cap);
}

HashMap::~HashMap()
{
	for (int i = 0; i < cap; i++)
	{
		delete bucketList[i];
	}
	delete[] bucketList;
}

HashMap::HashMap(const HashMap& hm)
	: hashFunction{hm.hashFunction}, sz{hm.sz}, cap{hm.cap}
{
	bucketList = new Node*[cap];
	newBucketList = nullptr;

	bucketListCopy(bucketList, hm.bucketList, cap);
}

HashMap& HashMap::operator=(const HashMap& hm)
{
	if (this != &hm)
	{
		newBucketList = new Node*[hm.cap];
		bucketListCopy(newBucketList, hm.bucketList, cap);

		//newBucketList = hm.newBucketList;
		sz = hm.sz;
		cap = hm.cap;

		delete[] bucketList;
		bucketList = newBucketList;
	}

	return *this;
}

unsigned int HashMap::bucketCount() const
{
	return cap;
}

unsigned int HashMap::size() const
{
	return sz;
}

double HashMap::loadFactor() const
{
	return (double) size() / bucketCount();
}

bool HashMap::contains(const std::string& key) const
{
	int index = hashFunction(key) % cap;

	if (!bucketList[index])
	{
		return false;
	}
	else
	{
		Node* current = bucketList[index];
		while (current != nullptr)
		{
			if (current -> key == key)
			{
				return true;
			}
			current = current -> next;
		}
		return false;
	}
}

void HashMap::add(const std::string& key, const std::string& value)
{
	unsigned int index = hashFunction(key) % cap;

	if (!contains(key))
	{
		addKeyValueToBucket(key, value, index);
	} 

	if (loadFactor() > .8)
	{
		unsigned int newCap = cap * 2 + 1;
		newBucketList = new Node*[newCap];

		rehashElements(cap, newCap);
		delete[] bucketList;
		bucketList = newBucketList;
		cap = newCap;
	}
}

bool HashMap::remove(const std::string& key)
{
	unsigned int index = hashFunction(key) % cap;

	if (!contains(key))
	{
		return false;
	}
	else
	{
		Node* current = bucketList[index];
		if (current -> key == key)
		{
			bucketList[index] = current -> next;
			delete current;
			sz--;
			return true;
		}
		else
		{
			Node* prev = current;
			current = current -> next;
			while (true)
			{
				if (current -> key == key)
				{
					prev -> next = current -> next;
					delete current;
					sz--;
					return true;
				}
				prev = current;
				current = current -> next;
			}
		}
	}
}


//Need to Fix this
std::string HashMap::value(const std::string& key) const
{
	unsigned int index = hashFunction(key) % cap;

	Node* current = bucketList[index];

	while (current != nullptr)
	{
		if (current -> key == key)
		{
			return current -> value;
		}
		current = current -> next;
	}

	return "";
}

unsigned int HashMap::maxBucketSize() const
{
	unsigned int maxSoFar = 0;

	for (int i = 0; i < cap; i++)
	{
		unsigned int temp = 0;

		if (bucketList[i])
		{
			Node* current = bucketList[i];
			while (current != nullptr)
			{
				temp = temp + 1;
				current = current -> next;
			}
		}

		if (temp > maxSoFar)
		{
			maxSoFar = temp;
		}
	}

	return maxSoFar;
}



// helper functions

void HashMap::createFirstArray(Node** &bucketList, unsigned int size)
{
    for (int i = 0; i < size; i++)
    {
        bucketList[i] = nullptr;
    }
}

void HashMap::bucketListCopy(Node** target, Node** source, unsigned int cap)
{
	for (int i = 0; i < cap; i++)
	{
		target[i] = source[i];
	}
}

void HashMap::addKeyValueToBucket(const std::string& key, const std::string& value, int index)
{
	if (!bucketList[index])
	{
		Node* newNode = new Node;
		newNode -> key = key;
		newNode -> value = value;
		newNode -> next = nullptr;
		bucketList[index] = newNode;
		sz++;
	}
	else
	{
		//testing that if bucket is not empty skips first condition
		// need to figure out how reference here works with assigning new head
		Node* newNode = new Node;
		newNode -> key = key;
		newNode -> value = value;
		newNode -> next = bucketList[index];
		bucketList[index] = newNode;
		sz++;
	}
}

void HashMap::addKeyValueToNewBucket(const std::string& key, const std::string& value, int index)
{
	if (!newBucketList[index])
	{
		Node* newNode = new Node;
		newNode -> key = key;
		newNode -> value = value;
		newNode -> next = nullptr;
		newBucketList[index] = newNode;
	}
	else
	{
		//testing that if bucket is not empty skips first condition
		// need to figure out how reference here works with assigning new head
		Node* newNode = new Node;
		newNode -> key = key;
		newNode -> value = value;
		newNode -> next = newBucketList[index];
		newBucketList[index] = newNode;
	}
}

void HashMap::printBucketList()
{
	for (int i = 0; i < cap; i++)
	{
		if (!bucketList[i])
		{
			std::cout << "-----empty bucket #" << i << "-----" << std::endl;
		}
		else
		{
			std::cout << "-----bucket number #" << i << "-----" << std::endl;
			Node* current = bucketList[i];
			while (current != nullptr)
			{
				std::cout << current->key << " " << current->value << std::endl;
				current = current->next;
			}
		}
	}
}

void HashMap::rehashElements(unsigned int cap, unsigned int newCap)
{
	for (int i = 0; i < cap; i++)
	{
		Node* current = bucketList[i];

		while (current != nullptr)
		{
			unsigned int newIndex = hashFunction(current -> key) % newCap;
			addKeyValueToNewBucket(current -> key, current -> value, newIndex);

			current = current -> next;
		}
	}
}

void HashMap::clearBucketList()
{
	newBucketList = new Node*[cap];
	bucketList = newBucketList;
	sz = 0;
	delete[] newBucketList;
}