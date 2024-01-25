package gomod

import (
	"os"
	"testing"
)

func TestExample(t *testing.T) {
	var dir = t.TempDir()
	var err = os.MkdirAll(dir, os.FileMode(750))
	if err != nil {
		t.Errorf("mkdir directory err, %f", err)
	}
}

func TestLru(t *testing.T) {

	cache := NewLRUCache(2)

	cache.Put(1, 1)
	cache.Display() // Output: (1:1)

	cache.Put(2, 2)
	cache.Display() // Output: (2:2) (1:1)

	if cache.Get(1) != 1 {
		t.Errorf("not equal")
	}

	cache.Display() // Output: (1:1) (2:2)

	cache.Put(3, 3)
	cache.Display() // Output: (3:3) (1:1)

	if cache.Get(2) != -1 {
		t.Errorf("not equal")
	}
}

func TestMain(t *testing.M) {
	t.Run()
}
