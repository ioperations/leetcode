package gomod

import (
	"container/list"
	"fmt"
)

type LRUCache struct {
	capacity int
	cache    map[int]*list.Element
	list     *list.List
}

type entry struct {
	key   int
	value int
}

func NewLRUCache(capacity int) *LRUCache {
	return &LRUCache{
		capacity: capacity,
		cache:    make(map[int]*list.Element),
		list:     list.New(),
	}
}

func (lru *LRUCache) Get(key int) int {
	if element, exists := lru.cache[key]; exists {
		lru.list.MoveToFront(element)
		return element.Value.(*entry).value
	}
	return -1
}

func (lru *LRUCache) Put(key int, value int) {
	if element, exists := lru.cache[key]; exists {
		// Update the value if the key already exists
		element.Value.(*entry).value = value
		lru.list.MoveToFront(element)
	} else {
		// Add a new entry
		if len(lru.cache) >= lru.capacity {
			// Remove the least recently used entry
			oldest := lru.list.Back()
			delete(lru.cache, oldest.Value.(*entry).key)
			lru.list.Remove(oldest)
		}

		// Add the new entry to the front of the list
		newElement := lru.list.PushFront(&entry{key, value})
		lru.cache[key] = newElement
	}
}

func (lru *LRUCache) Display() {
	for element := lru.list.Front(); element != nil; element = element.Next() {
		fmt.Printf("(%v:%v) ", element.Value.(*entry).key, element.Value.(*entry).value)
	}
	fmt.Println()
}
