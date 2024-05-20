package main

import (
	"log"
	"net/http"
)

func main() {

	log.Println("Start server at http://localhost:8080 ... (Press Ctrl + C to stop)")
	log.Fatal(http.ListenAndServe(":8080",
		http.FileServer(http.Dir("./assets"))))
}
