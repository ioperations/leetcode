package gomod

import (
	"testing"
)

func TestT1(t *testing.T) {
	var sl Solution
	var output = sl.SimplifyPath("/home/")
	if output != "/home" {
		t.Errorf("not equal")
	}
}

func TestT2(t *testing.T) {
	var sl Solution
	var output = sl.SimplifyPath("/../")
	if output != "/" {
		t.Errorf("not equal")
	}
}

func TestT3(t *testing.T) {
	var sl Solution
	var output = sl.SimplifyPath("/home//foo/")
	if output != "/home/foo" {
		t.Errorf("not equal")
	}
}
