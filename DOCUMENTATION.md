# Pengo Framework Design
Author: Loi Nguyen <loint@penlook.com>  |  Date: 05/10/2015 

### Pengo Cli
+ Create new application

```bash
pengo new app
```

+ Create new action

```bash
pengo new home:index
```

+ Create new entity

```bash
pengo new mysql>user
```

+ Create new view

```bash
pengo new home/index
```

+ Run application under debugging mode

```bash
pengo run app
```

+ Build application and ready for production

```bash
pengo build app
```

+ Analyze application for debugging mode

```bash
pengo debug router
```
```bash
pengo debug controller
```
```bash
pengo debug model
```

### Pengo Controller

+ Controller declaration
```go
@Controller app
```

+ Controller declaration and extend from base controller
```go
@Controller app base
```

+ Router - Method - Action mapping
```go
@Router /hello/:userid/:password
@Method GET POST PUT
func Login(userid int, password string) {
}
```

### Pengo Model

+ Select user who has id = 3 from user table
```go
user := mysql>User 
listUser = user.Find({
	Id: 3
})
```

+ Create new status
```go
status := mongo>Status {
	Username: "loint",
	Content: "Have a nice day !",
}
status.Create()
```

+ Save login information using session
```go
session>Username = "loint"
session>Login = true 
```

+ Assign and retrive dynamic key to redis
```go
redis>"abc" = "hello"
fmt.Println(redis>"abc")
```

### Pengo Template
+ Assign function variable to template
```go
$compress = func(html string) {
	return html + " is using compress function"
}
```

+ Assign normal variable to template
```go
$title = "Pengo Application"	
$message = "Hello World"
```

+ Template manipulation
```html
<html>
	<title>{{ title }}</title>
<body>
	<h1>{{ message }}</h1>
	<p>{{ "abc" | compress }}</p>	
</body>
</html>
```

### Pengo Testing

+ Setup
```go
func Setup() {
}
```

+ Testing
```go
@Test
func Login() {
}
```

+ Teardown
```go
func Teardown() {
}
```

+ Assertion Equal (assert.Equal)
```go
person := Person {
	Name: "Loi Nguyen",
	Age: 21,
}
person.Age == 21 ?
```

+ Assertion Not Nil (assert.NotNil)
```go
person.Age != nil ?
```

+ Assertion True
```go
person.Age ?
```

+ Assertion False
```go
! person.Age ?
```
