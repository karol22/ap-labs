package main

import (
	"fmt"
	"os"
	"io/ioutil"
	"log"
	"path/filepath"
)

// scanDir stands for the directory scanning implementation
func scanDir(dir string) error {
	return nil
}

func main() {

	directories:=0
	symLinks :=0
	otherFiles := 0

	//case if no argument os provided
	if len(os.Args) < 2 {
		fmt.Println("    Usage: ./dir-scan <directory>\n")
		os.Exit(1)
	}
	_, err := ioutil.ReadDir(os.Args[1])
    if err != nil {
        log.Fatal(err)
    }
	mainFolder := os.Args[1]
	err = filepath.Walk(mainFolder, func (path string, info os.FileInfo, err error) error {
		//fmt.Println(path)
		mode:= info.Mode()
		_, err = os.Stat(path)
		if err != nil {
			fmt.Println(err)
			return err
		}
		if info.IsDir() {
			directories++
		} else if mode&os.ModeSymlink != 0 {
			symLinks ++
		} else {
			otherFiles ++
		}
		return nil
	})
	printAns(mainFolder, directories, symLinks, otherFiles)

}

func printAns (mainPath string, directories, symLinks, otherFiles int){
	fmt.Printf("Directoy scanner tool\n")
	fmt.Printf("Path         ")
	fmt.Printf(mainPath)
	fmt.Printf("\nDirectories				    %v\n", directories)
	fmt.Printf("Symbolic Links   	         	%v\n", symLinks)
	fmt.Printf("Other files			     	    %v\n", otherFiles)
}
