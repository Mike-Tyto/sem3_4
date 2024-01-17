package main
 
import (
"fmt"
"net/http"
"os"
"io"
)

func file_writer(str []byte) {
	// fmt.Println(string(str))
	f,err := os.Create("test.txt")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer f.Close()
	f.Write(str)
}

func main() {
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		// fmt.Fprintf(w, "Hello World!")
		if r == nil {
			return
		}
		defer r.Body.Close()
		body := r.Body
		buffer, _ := io.ReadAll(body)
		file_writer(buffer)
	})
	http.ListenAndServe(":8080", nil)
}
