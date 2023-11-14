import sys
from prompt_toolkit import prompt
from prompt_toolkit.completion import WordCompleter
import requests

API_URL = "http://127.0.0.1/"

def list_agents():
    try:
        response = requests.get(f"{API_URL}/agents")
        response.raise_for_status()
        return response.json()
    except requests.RequestException as e:
        return f"Error: {e}"

def list_results():
    try:
        response = requests.get(f"{API_URL}/results")
        response.raise_for_status()
        return response.json()
    except requests.RequestException as e:
        return f"Error: {e}"

def post_task():
    implant_id = prompt('Enter implant ID: ')
    command = prompt('Enter command: ')
    task_data = f"{implant_id},,{command}"
    try:
        response = requests.post(f"{API_URL}/tasks", task_data)
        response.raise_for_status()
        return response.json()
    except requests.RequestException as e:
        return f"Error: {e}"

def start_service():
    try:
        response = requests.get(f"{API_URL}:8888/listeners")
        response.raise_for_status()
        return response.json()
    except requests.RequestException as e:
        return f"Error: {e}"

def stop_service():
    try:
        response = requests.post(f"{API_URL}:8888/listeners")
        response.raise_for_status()
        return response.json()
    except requests.RequestException as e:
        return f"Error: {e}"

def help_message():
    return """
        list_agents - Lists all agents
        list_results - Lists all results
        post_task - Posts a new task
        start_service - Starts the service
        stop_service - Stops the service
        help - Shows this help message
        exit - Exits the program
    """

def main():
    command_completer = WordCompleter([
        'list_agents', 'list_results', 'post_task', 
        'start_service', 'stop_service', 'help', 'exit'
    ])

    commands = {
        'list_agents': list_agents,
        'list_results': list_results,
        'post_task': post_task,
        'start_service': start_service,
        'stop_service': stop_service,
        'help': help_message,
        'exit': lambda: sys.exit()
    }

    while True:
        user_input = prompt('Enter command: ', completer=command_completer)
        action = commands.get(user_input, lambda: "Unknown command. Type 'help' for a list of commands.")
        print(action() if callable(action) else action)

if __name__ == "__main__":
    main()
