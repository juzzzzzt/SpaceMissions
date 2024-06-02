import sys
import wikipedia


def fetch_wikipedia_summary(url):
    try:
        title = url.split("/")[-1]
        summary = wikipedia.summary(title)
        return summary
    except wikipedia.DisambiguationError as e:
        return "Disambiguation error: " + str(e.options)
    except wikipedia.PageError as e:
        return "Page error: " + str(e)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Error: No URL provided")
        sys.exit(1)

    url = sys.argv[1]
    summary = fetch_wikipedia_summary(url)

    if isinstance(summary, str):
        # Ensure proper encoding for stdout
        sys.stdout.buffer.write(summary.encode('utf-8'))
    else:
        print("An error occurred")
