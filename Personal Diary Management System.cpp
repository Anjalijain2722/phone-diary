from flask import Flask, request, jsonify

app = Flask(__name__)

# In-memory phone directory (like a database)
phone_directory = {}

@app.route('/')
def home():
    return "Welcome to Phone Directory!"

@app.route('/add', methods=['POST'])
def add_contact():
    data = request.get_json()
    name = data.get('name')
    number = data.get('number')

    if name in phone_directory:
        return jsonify({'message': 'Contact already exists!'}), 400
    else:
        phone_directory[name] = number
        return jsonify({'message': 'Contact added successfully!'})

@app.route('/view', methods=['GET'])
def view_contacts():
    return jsonify(phone_directory)

@app.route('/search/<name>', methods=['GET'])
def search_contact(name):
    number = phone_directory.get(name)
    if number:
        return jsonify({name: number})
    else:
        return jsonify({'message': 'Contact not found!'}), 404

@app.route('/delete/<name>', methods=['DELETE'])
def delete_contact(name):
    if name in phone_directory:
        del phone_directory[name]
        return jsonify({'message': 'Contact deleted successfully!'})
    else:
        return jsonify({'message': 'Contact not found!'}), 404

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
