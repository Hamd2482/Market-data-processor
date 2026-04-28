import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt

st.set_page_config(layout="wide")
st.title("📊 Market Data Processor Dashboard")

df = pd.read_csv("mdp_output.csv", names=["bid", "ask", "spread", "mid"])

col1, col2, col3 = st.columns(3)
col1.metric("Latest Bid", int(df["bid"].iloc[-1]))
col2.metric("Latest Ask", int(df["ask"].iloc[-1]))
col3.metric("Spread", int(df["spread"].iloc[-1]))

st.markdown("---")

col1, col2 = st.columns(2)

with col1:
    fig1, ax1 = plt.subplots(figsize=(5,3))
    ax1.plot(df["bid"], label="Bid")
    ax1.plot(df["ask"], label="Ask")
    ax1.legend()
    ax1.set_title("Bid vs Ask")
    st.pyplot(fig1)

with col2:
    fig2, ax2 = plt.subplots(figsize=(5,3))
    ax2.plot(df["spread"])
    ax2.set_title("Spread")
    st.pyplot(fig2)