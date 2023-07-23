# KusServer Documentation
KusServer is a tool for setup and maintain a server on C++.

KusServer provides:

No guarantee | No warranty | No return

# Server Setup

KusServer uses vcpkg to manage libraries for cmake by specifing toolchain file in CMakeLists.txt file.

KusServer requires the following libraries:

	boost
	libpqxx
	crow

## Automated remote server deploy
To start the server, run the file /devops/setup/server_setup.bat. 
This file extracts server configuration information from the local bat file. 
The path to this bat file stored in the file /devops/setup/scripts/key.bat. 
The local configuration file should contain the following information:

	# IP address of the server
	set ip=127.0.0.2

	# name of root user
	set server_name=root
	# password for root user
	set server_password=12345

	# name of a user with sudo access to be created
	set user_name=user
	# password for created user
	set user_password=12345

	# name of your domain
	set domain=kussystem.ru
	# mail for letsencrypt
	set domain_mail=kussystem@mail.ru

	# url for cloning the current project
	set project_url=https://github.com/r-comrad/server_v4
	# url for cloning a data project (contains frontend code and static data for server)
	set data_url=https://github.com/rcomrad/data

	# path for generated ssh keys
	set key_dir=D:/keys/
	# path to windows ssh folder
	set win_ssh_dir=C:\Users\r_comrad\.ssh

	# git user name (for git config)
	set git_name=r_comrad
	# git mail (for git config)
	set git_maile=git_maile@mail.ru

## Database connection settings
The server uses postgresql to store data.
In order to make queries to the database, the bin folder of the server project must contain the database.pass file. 
The contents of the file define parameters for creating database connections, such as database name, username, schema.
This file has the following structure:

	user_type database_name user_name user_pasword schema_name

user_type corresponds to the user mode for this particular parameters. 
You must specify exactly one set of parameters (parameter triplet - database  username schema) for each user mode.
There are two user mods:
	
	0 # For ADMIN connection
	1 # For USER connection

Thus, the database.pass file could contain the following lines:

	0 postgres postgres 12345 public
	1 my_database user 12345 my_schema

## Program settings
KusServer uses variables to store the user settings of the server instance.
To configure a variable, you must write it to the main_settings.conf file in the bin directory.
KasServer supports the following settings:


	# Sets the number of database connections used by the server
	database_connection_count 3
	# Sets the number of threads for submission testing (programming problems)
	tester_thread_count 1

	# Force the server to execute the restart command at startup.
	# This type of command can reconfigure the database, add or delete data.
	restart_on_start nun

	
	# Set the flag for submission online testing (programming problems)
	submission_auto_check off
	# Set the flag for simple answers online testing
	answer_auto_check on

	# Set the flag to implement authorization
	authorisation off

# Testing

### nginx

You can check if nginx is configured correctly by sending a /test request.
For example https://kussystem.ru/test.
If nginx setup is successful, you will receive the following message:

	Hello from nginx!

### KusServer process

To check whether the server process is running, you can use /api/test request.
For example https://kussystem.ru/api/test.
Provided that the server process is capable of performing basic functional, you will receive the following message:

	All fine!

### postman test

To test the API, you can use postman test, located in the test folder in the postman_tests.json file.

# API Description

## Authentication (/api/login) | POST

To log in, the user must use authentication post-request and specify the username and password in the request body.

Result: If authentication was successful, the result will contain 
user object (ID, login, user roles, token if any, and other data).
401 Unauthorized otherwise.

	example:
	/api/login
	{
		"login": "user",
		"password": "12345"
	}

## Get data (/api/get/<string: mode>/<string: data request>) | GET

The get request retrieves data from the database in JSON format. 
This data object can be aggregated from various tables.
In order to make a get data request, you must specify get mode, data request, and an optional condition.

### request mods

There are three mods for the get request:

1) /api/get/all/<string: data request> - returns all objects for given request

2) /api/get/by_id/<string: data request>/<string: id> - returns an object with the specified ID

3) /api/get/if/<string: data request>/<string: condition> - returns objects that match the specified criteria

### data request rules - brackets

To select specific table columns or to insert data from another database table
corresponding to specified column, you can use brackets - [ ].
For example, if you use the following query, you will receive a complete user object (all columns of the table).

	/api/get/all/user
	/api/get/all/user[*] # the * symbol will insert names of all columns

But if you want to get only the user id and his roles you can use this:

	/api/get/all/user[id,role]

Finally, to add information about the user's organization or other data with one-to-many relation, use this:

	/api/get/all/user[organisation[id,name,address]]

### data request rules - parentheses

Parentheses ( ) also help you with the one-to-many relations, but this relationship should have the opposite direction.
Using the example above, if you want to add all users for a specific organization, you can use the following request:

	/api/get/all/organisation[id,(user[name,role])]

In order for the parentheses to work, you must select an id column for the caller object (in this example for the organization).

## Insert/Update request (/api/post/<string: TableName>) | POST

All URLs of POST insert/update requests end with the name of the target table (object table).

POST insert request allows you to insert data in app database. There are three request mods:

### 1) insert new object: `-id, all data`

If you want to insert a completely new object into the database, you must specify all the object data 
in the body of the post request, except for the object ID (or with an identifier equal to zero).

Result: ID of the created object

### 2) update existing object: `id, some data`

To update an existing object, you must specify the ID of the target object. 
After that, you can freely choose which data you want to change: 
if some property of the object is excluded from the body of the post request, when it will not be changed.

Result: ID of the updated object

### 3) many-ro-many request: `many-to-many type, (-id, all data)/(id, some data), arrays of indexes`

Firstly, if you do not specify the object ID (or its identifier is zero),
then the specified data will be used to create a new object using the rules of the insert new object function,
and the resulting identifier will be used in the next step. Otherwise data will be used to update the object 
with the specified ID using the rules for updating existing object function.

To insert "Many to Many" relation, you need to specify 
the many_to_many field in the request body with one of two values:

- add - add connections to existing ones 

- replace - create a new connection and delete old ones (delete all connection with the selected object - by ID).

The "Many to many" request connects selected object from the <string: TableName> 
with all objects from the array of IDs specified as a parameter of the request body. 
The name of the array property must match the TableName of the objects.

Result: Unknown

	example:
	/api/post/competition
	{
		"many_to_many" : "add",
		"name": "Пробный тур",
		"start_time": "2023-04-02 15:00:00",
		"end_time": "2023-04-03 00:00:00",
		"problem": [
			1,
			2
		],
		"question": [
			1,
			2
		]
	}
