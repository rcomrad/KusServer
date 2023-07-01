# KusServer documentation
KusServer is a cross-platform tool for configuring a server and supporting its API on C++.

KusServer provides:

No guarantee | No warranty | No return

# Server setup
To start the server, run the file /devops/setup/server_setup.bat. 
This file extracts server configuration information from the local bat file. 
The path to this bat file stored in the file /devops/setup/scripts/key.bat. 
The local configuration file contains the following information

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

# API description
## POST Insert|Update request (/api/post/<string: TableName>)

All URLs of POST Insert|Update requests end with the name of the target table (object table).

POST Insert request allows you to insert data in app database. There are three request mods:

### 1) insert new object: `-id, all data`

If you want to insert a completely new object into the database, you must specify all the object data 
in the body of the post request, except for the object ID (or with an identifier equal to zero).

Result: ID of the created object

### 2) update existing object: `id, some data`

To update an existing object, you must specify the ID of the target object. 
After that, you can freely choose which data you want to change: 
if some property of the object is excluded from the body of the post request, when it will not be changed.

Result: ID of the updated object

### 3) Many-To-Many request: `many-to-many type, (-id, all data)/(id, some data), arrays of indexes`

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
