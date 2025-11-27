from bs4 import BeautifulSoup
import requests

html = requests.get("https://www.amazon.com.br/gp/cart/view.html?ref_=nav_cart").content
soup = BeautifulSoup(html, "html.parser")

for item in soup.find_all("div", class_="a-price-whole"):
    print(item.get_text())
