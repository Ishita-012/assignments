
# NLP Chatbot - Doc Bot
!pip install newspaper3k lxml_html_clean

import random
import nltk
from newspaper import Article
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity

# Download required NLTK data
nltk.download('punkt', quiet=True)
nltk.download('punkt_tab', quiet=True)

# Download and read article
url = "https://www.bbc.com/news/health-54500673"

article = Article(url)
article.download()
article.parse()

corpus = article.text

# Split article into sentences
sentence_list = nltk.sent_tokenize(corpus)

print("Doc Bot: I am Doc Bot. Ask me questions about kidney disease.")
print("Type 'bye' to exit.")

# Greeting function
def greeting_response(text):
    greetings = ["hi", "hello", "hey", "hola", "greetings"]

    for word in text.lower().split():
        if word in greetings:
            return random.choice(["Hello!", "Hey!", "Hi there!"])

    return None

# Find the most similar sentences
def bot_response(user_input):

    sentences = sentence_list + [user_input]

    vector = CountVectorizer().fit_transform(sentences)
    scores = cosine_similarity(vector[-1], vector[:-1]).flatten()

    indexes = scores.argsort()[::-1]

    response = []
    for i in indexes:
        if scores[i] > 0:
            response.append(sentence_list[i])
        if len(response) == 3:
            break

    if response:
        return " ".join(response)
    else:
        return "Sorry, I don't understand. Please ask another question."

# Chat loop
while True:
    user_input = input("\nYou: ").strip()

    if user_input.lower() in ["bye", "exit", "quit", "break",
                              "see you later"]:
        print("Doc Bot: Chat with you later!")
        break

    greeting = greeting_response(user_input)

    if greeting:
        print("Doc Bot:", greeting)
    else:
        print("Doc Bot:", bot_response(user_input))
